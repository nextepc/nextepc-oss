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

static af_context_t self;

int __af_log_domain;

static OGS_POOL(af_sess_pool, af_sess_t);

static int context_initialized = 0;

void af_context_init(void)
{
    ogs_assert(context_initialized == 0);

    /* Initialize AF context */
    memset(&self, 0, sizeof(af_context_t));

    ogs_log_install_domain(&__af_log_domain, "af", ogs_core()->log.level);

    ogs_pool_init(&af_sess_pool, ogs_app()->pool.sess);

    self.supi_hash = ogs_hash_make();
    self.ipv4_hash = ogs_hash_make();
    self.ipv6_hash = ogs_hash_make();

    context_initialized = 1;
}

void af_context_final(void)
{
    ogs_assert(context_initialized == 1);

    af_sess_remove_all();

    ogs_assert(self.supi_hash);
    ogs_hash_destroy(self.supi_hash);
    ogs_assert(self.ipv4_hash);
    ogs_hash_destroy(self.ipv4_hash);
    ogs_assert(self.ipv6_hash);
    ogs_hash_destroy(self.ipv6_hash);

    ogs_pool_final(&af_sess_pool);

    context_initialized = 0;
}

af_context_t *af_self(void)
{
    return &self;
}

static int af_context_prepare(void)
{
    self.nf_type = OpenAPI_nf_type_AF;

    return OGS_OK;
}

static int af_context_validation(void)
{
    return OGS_OK;
}

int af_context_parse_config(void)
{
    int rv;
    yaml_document_t *document = NULL;
    ogs_yaml_iter_t root_iter;

    document = ogs_app()->document;
    ogs_assert(document);

    rv = af_context_prepare();
    if (rv != OGS_OK) return rv;

    ogs_yaml_iter_init(&root_iter, document);
    while (ogs_yaml_iter_next(&root_iter)) {
        const char *root_key = ogs_yaml_iter_key(&root_iter);
        ogs_assert(root_key);
        if (!strcmp(root_key, "af")) {
            ogs_yaml_iter_t af_iter;
            ogs_yaml_iter_recurse(&root_iter, &af_iter);
            while (ogs_yaml_iter_next(&af_iter)) {
                const char *af_key = ogs_yaml_iter_key(&af_iter);
                ogs_assert(af_key);
                if (!strcmp(af_key, "sbi")) {
                    /* handle config in sbi library */
                } else
                    ogs_warn("unknown key `%s`", af_key);
            }
        }
    }

    rv = af_context_validation();
    if (rv != OGS_OK) return rv;

    return OGS_OK;
}

af_sess_t *af_sess_add_by_snssai_and_dnn(ogs_s_nssai_t *s_nssai, char *dnn)
{
    af_sess_t *sess = NULL;

    ogs_assert(s_nssai);
    ogs_assert(s_nssai->sst);
    ogs_assert(dnn);

    ogs_pool_alloc(&af_sess_pool, &sess);
    if (!sess) {
        ogs_error("Maximum number of session[%lld] reached",
            (long long)ogs_app()->pool.sess);
        return NULL;
    }
    memset(sess, 0, sizeof *sess);

    /* SBI Features */
    OGS_SBI_FEATURES_SET(sess->management_features,
            OGS_SBI_NBSF_MANAGEMENT_BINDING_UPDATE);

    sess->s_nssai.sst = s_nssai->sst;
    sess->s_nssai.sd.v = s_nssai->sd.v;

    sess->dnn = ogs_strdup(dnn);
    ogs_assert(sess->dnn);

    sess->binding_id = ogs_msprintf("%d",
            (int)ogs_pool_index(&af_sess_pool, sess));
    ogs_assert(sess->binding_id);

    ogs_list_add(&self.sess_list, sess);

    return sess;
}

void af_sess_remove(af_sess_t *sess)
{
    int i;

    ogs_assert(sess);

    ogs_list_remove(&self.sess_list, sess);

    /* Free SBI object memory */
    ogs_sbi_object_free(&sess->sbi);

    ogs_assert(sess->binding_id);
    ogs_free(sess->binding_id);

    if (sess->supi)
        ogs_free(sess->supi);
    if (sess->gpsi)
        ogs_free(sess->gpsi);

    if (sess->ipv4addr)
        ogs_free(sess->ipv4addr);
    if (sess->ipv6prefix)
        ogs_free(sess->ipv6prefix);

    ogs_assert(sess->dnn);
    ogs_free(sess->dnn);

    if (sess->pcf_fqdn)
        ogs_free(sess->pcf_fqdn);

    for (i = 0; i < sess->num_of_addr; i++) {
        if (sess->addr[i].ipv4)
            ogs_freeaddrinfo(sess->addr[i].ipv4);
        if (sess->addr[i].ipv6)
            ogs_freeaddrinfo(sess->addr[i].ipv6);
    }
    sess->num_of_addr = 0;

    ogs_pool_free(&af_sess_pool, sess);
}

void af_sess_remove_all(void)
{
    af_sess_t *sess = NULL, *next_sess = NULL;

    ogs_list_for_each_safe(&self.sess_list, next_sess, sess)
        af_sess_remove(sess);
}

af_sess_t *af_sess_find(uint32_t index)
{
    return ogs_pool_find(&af_sess_pool, index);
}

af_sess_t *af_sess_find_by_snssai_and_dnn(ogs_s_nssai_t *s_nssai, char *dnn)
{
    af_sess_t *sess = NULL;

    ogs_assert(s_nssai);
    ogs_assert(dnn);

    ogs_list_for_each(&self.sess_list, sess)
        if (sess->s_nssai.sst == s_nssai->sst &&
            sess->dnn && strcmp(sess->dnn, dnn) == 0)
            return sess;

    return NULL;
}

af_sess_t *af_sess_find_by_binding_id(char *binding_id)
{
    ogs_assert(binding_id);
    return af_sess_find(atoll(binding_id));
}

void af_sess_select_nf(af_sess_t *sess, OpenAPI_nf_type_e nf_type)
{
    ogs_assert(sess);
    ogs_assert(nf_type);

    if (nf_type == OpenAPI_nf_type_NRF)
        ogs_sbi_select_nrf(&sess->sbi, af_nf_state_registered);
    else
        ogs_sbi_select_first_nf(&sess->sbi, nf_type, af_nf_state_registered);
}
