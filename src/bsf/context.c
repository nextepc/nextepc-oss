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

static bsf_context_t self;

int __bsf_log_domain;

static OGS_POOL(bsf_ue_pool, bsf_ue_t);
static OGS_POOL(bsf_sess_pool, bsf_sess_t);

static int context_initialized = 0;

void bsf_context_init(void)
{
    ogs_assert(context_initialized == 0);

    /* Initialize BSF context */
    memset(&self, 0, sizeof(bsf_context_t));

    ogs_log_install_domain(&__bsf_log_domain, "bsf", ogs_core()->log.level);

    ogs_pool_init(&bsf_ue_pool, ogs_app()->max.ue);
    ogs_pool_init(&bsf_sess_pool, ogs_app()->pool.sess);

    self.supi_hash = ogs_hash_make();
    self.ipv4_hash = ogs_hash_make();
    self.ipv6_hash = ogs_hash_make();

    context_initialized = 1;
}

void bsf_context_final(void)
{
    ogs_assert(context_initialized == 1);

    bsf_ue_remove_all();

    ogs_assert(self.supi_hash);
    ogs_hash_destroy(self.supi_hash);
    ogs_assert(self.ipv4_hash);
    ogs_hash_destroy(self.ipv4_hash);
    ogs_assert(self.ipv6_hash);
    ogs_hash_destroy(self.ipv6_hash);

    ogs_pool_final(&bsf_ue_pool);
    ogs_pool_final(&bsf_sess_pool);

    context_initialized = 0;
}

bsf_context_t *bsf_self(void)
{
    return &self;
}

static int bsf_context_prepare(void)
{
    self.nf_type = OpenAPI_nf_type_BSF;

    return OGS_OK;
}

static int bsf_context_validation(void)
{
    return OGS_OK;
}

int bsf_context_parse_config(void)
{
    int rv;
    yaml_document_t *document = NULL;
    ogs_yaml_iter_t root_iter;

    document = ogs_app()->document;
    ogs_assert(document);

    rv = bsf_context_prepare();
    if (rv != OGS_OK) return rv;

    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);
        if (!strcmp(root_key, "bsf")) {
            ogs_yaml_iter_t bsf_iter;
            ogs_yaml_iter_recurse(&root_iter, &bsf_iter);
            while (ogs_yaml_iter_next(&bsf_iter)) {
                const char *bsf_key = ogs_yaml_iter_key(&bsf_iter);
                ogs_assert(bsf_key);
                if (!strcmp(bsf_key, "sbi")) {
                    /* handle config in sbi library */
                } else
                    ogs_warn("unknown key `%s`", bsf_key);
            }
        }
    }

    rv = bsf_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}

bsf_ue_t *bsf_ue_add_by_supi(char *supi)
{
    bsf_ue_t *bsf_ue = NULL;

    ogs_assert(supi);

    ogs_pool_alloc(&bsf_ue_pool, &bsf_ue);
    ogs_assert(bsf_ue);
    memset(bsf_ue, 0, sizeof *bsf_ue);

    ogs_list_init(&bsf_ue->sess_list);

    bsf_ue->supi = ogs_strdup(supi);
    ogs_assert(bsf_ue->supi);
    ogs_hash_set(self.supi_hash, bsf_ue->supi, strlen(bsf_ue->supi), bsf_ue);

    ogs_list_add(&self.bsf_ue_list, bsf_ue);

    ogs_info("[Added] Number of BSF-UEs is now %d",
            ogs_list_count(&self.bsf_ue_list));

    return bsf_ue;
}

void bsf_ue_remove(bsf_ue_t *bsf_ue)
{
    ogs_assert(bsf_ue);

    ogs_list_remove(&self.bsf_ue_list, bsf_ue);

#if 0
    bsf_sess_remove_all(bsf_ue);
#endif

    if (bsf_ue->supi) {
        ogs_hash_set(self.supi_hash, bsf_ue->supi, strlen(bsf_ue->supi), NULL);
        ogs_free(bsf_ue->supi);
    }

    ogs_pool_free(&bsf_ue_pool, bsf_ue);

    ogs_info("[Removed] Number of BSF-UEs is now %d",
            ogs_list_count(&self.bsf_ue_list));
}

void bsf_ue_remove_all(void)
{
    bsf_ue_t *bsf_ue = NULL, *next = NULL;;

    ogs_list_for_each_safe(&self.bsf_ue_list, next, bsf_ue)
        bsf_ue_remove(bsf_ue);
}

bsf_ue_t *bsf_ue_find_by_supi(char *supi)
{
    ogs_assert(supi);
    return (bsf_ue_t *)ogs_hash_get(self.supi_hash, supi, strlen(supi));
}

void bsf_sess_select_nf(bsf_sess_t *sess, OpenAPI_nf_type_e nf_type)
{
    ogs_assert(sess);
    ogs_assert(nf_type);

    if (nf_type == OpenAPI_nf_type_NRF)
        ogs_sbi_select_nrf(&sess->sbi, bsf_nf_state_registered);
    else
        ogs_sbi_select_first_nf(&sess->sbi, nf_type, bsf_nf_state_registered);
}
