/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "context.h"

static sepp_context_t self;

int __sepp_log_domain;

static OGS_POOL(sepp_ue_pool, sepp_ue_t);
static OGS_POOL(sepp_sess_pool, sepp_sess_t);

static int context_initialized = 0;

void sepp_context_init(void)
{
    ogs_assert(context_initialized == 0);

    /* Initialize SEPP context */
    memset(&self, 0, sizeof(sepp_context_t));

    ogs_log_install_domain(&__sepp_log_domain, "sepp", ogs_core()->log.level);

    ogs_pool_init(&sepp_ue_pool, ogs_app()->max.ue);
    ogs_pool_init(&sepp_sess_pool, ogs_app()->pool.sess);

    self.supi_hash = ogs_hash_make();
    self.ipv4_hash = ogs_hash_make();
    self.ipv6_hash = ogs_hash_make();

    context_initialized = 1;
}

void sepp_context_final(void)
{
    ogs_assert(context_initialized == 1);

    sepp_ue_remove_all();

    ogs_assert(self.supi_hash);
    ogs_hash_destroy(self.supi_hash);
    ogs_assert(self.ipv4_hash);
    ogs_hash_destroy(self.ipv4_hash);
    ogs_assert(self.ipv6_hash);
    ogs_hash_destroy(self.ipv6_hash);

    ogs_pool_final(&sepp_ue_pool);
    ogs_pool_final(&sepp_sess_pool);

    context_initialized = 0;
}

sepp_context_t *sepp_self(void)
{
    return &self;
}

static int sepp_context_prepare(void)
{
    self.nf_type = OpenAPI_nf_type_SEPP;

    return OGS_OK;
}

static int sepp_context_validation(void)
{
    return OGS_OK;
}

int sepp_context_parse_config(void)
{
    int rv;
    yaml_document_t *document = NULL;
    ogs_yaml_iter_t root_iter;

    document = ogs_app()->document;
    ogs_assert(document);

    rv = sepp_context_prepare();
    if (rv != OGS_OK) return rv;

    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);
        if (!strcmp(root_key, "sepp")) {
            ogs_yaml_iter_t sepp_iter;
            ogs_yaml_iter_recurse(&root_iter, &sepp_iter);
            while (ogs_yaml_iter_next(&sepp_iter)) {
                const char *sepp_key = ogs_yaml_iter_key(&sepp_iter);
                ogs_assert(sepp_key);
                if (!strcmp(sepp_key, "sbi")) {
                    /* handle config in sbi library */
                } else
                    ogs_warn("unknown key `%s`", sepp_key);
            }
        }
    }

    rv = sepp_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}

sepp_ue_t *sepp_ue_add_by_supi(char *supi)
{
    sepp_ue_t *sepp_ue = NULL;

    ogs_assert(supi);

    ogs_pool_alloc(&sepp_ue_pool, &sepp_ue);
    ogs_assert(sepp_ue);
    memset(sepp_ue, 0, sizeof *sepp_ue);

    ogs_list_init(&sepp_ue->sess_list);

    sepp_ue->supi = ogs_strdup(supi);
    ogs_assert(sepp_ue->supi);
    ogs_hash_set(self.supi_hash, sepp_ue->supi, strlen(sepp_ue->supi), sepp_ue);

    ogs_list_add(&self.sepp_ue_list, sepp_ue);

    ogs_info("[Added] Number of SEPP-UEs is now %d",
            ogs_list_count(&self.sepp_ue_list));

    return sepp_ue;
}

void sepp_ue_remove(sepp_ue_t *sepp_ue)
{
    ogs_assert(sepp_ue);

    ogs_list_remove(&self.sepp_ue_list, sepp_ue);

#if 0
    sepp_sess_remove_all(sepp_ue);
#endif

    if (sepp_ue->supi) {
        ogs_hash_set(self.supi_hash, sepp_ue->supi, strlen(sepp_ue->supi), NULL);
        ogs_free(sepp_ue->supi);
    }

    ogs_pool_free(&sepp_ue_pool, sepp_ue);

    ogs_info("[Removed] Number of SEPP-UEs is now %d",
            ogs_list_count(&self.sepp_ue_list));
}

void sepp_ue_remove_all(void)
{
    sepp_ue_t *sepp_ue = NULL, *next = NULL;;

    ogs_list_for_each_safe(&self.sepp_ue_list, next, sepp_ue)
        sepp_ue_remove(sepp_ue);
}

sepp_ue_t *sepp_ue_find_by_supi(char *supi)
{
    ogs_assert(supi);
    return (sepp_ue_t *)ogs_hash_get(self.supi_hash, supi, strlen(supi));
}

void sepp_sess_select_nf(sepp_sess_t *sess, OpenAPI_nf_type_e nf_type)
{
    ogs_assert(sess);
    ogs_assert(nf_type);

    if (nf_type == OpenAPI_nf_type_NRF)
        ogs_sbi_select_nrf(&sess->sbi, sepp_nf_state_registered);
    else
        ogs_sbi_select_first_nf(&sess->sbi, nf_type, sepp_nf_state_registered);
}
