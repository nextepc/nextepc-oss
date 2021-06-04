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

#ifndef SEPP_CONTEXT_H
#define SEPP_CONTEXT_H

#include "ogs-sbi.h"
#include "ogs-app.h"

#include "timer.h"
#include "sepp-sm.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int __sepp_log_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __sepp_log_domain

typedef struct sepp_context_s {
    OpenAPI_nf_type_e   nf_type;

    ogs_hash_t      *supi_hash;     /* hash table (SUPI) */
    ogs_hash_t      *ipv4_hash;     /* hash table (IPv4 Address) */
    ogs_hash_t      *ipv6_hash;     /* hash table (IPv6 Address) */

#define SEPP_UE_IS_LAST_SESSION(__sMF) \
     ((__sMF) && (ogs_list_count(&(__sMF)->sess_list)) == 1)
    ogs_list_t      sepp_ue_list;
} sepp_context_t;

typedef struct sepp_ue_s {
    ogs_lnode_t lnode;

    /* SUPI */
    char *supi;

    ogs_list_t sess_list;
} sepp_ue_t;

#define SEPP_NF_INSTANCE_CLEAR(_cAUSE, _nFInstance) \
    do { \
        ogs_assert(_nFInstance); \
        if ((_nFInstance)->reference_count == 1) { \
            ogs_info("[%s] (%s) NF removed", (_nFInstance)->id, (_cAUSE)); \
            sepp_nf_fsm_fini((_nFInstance)); \
        } else { \
            /* There is an assocation with other context */ \
            ogs_info("[%s:%d] (%s) NF suspended", \
                    _nFInstance->id, _nFInstance->reference_count, (_cAUSE)); \
            OGS_FSM_TRAN(&_nFInstance->sm, sepp_nf_state_de_registered); \
            ogs_fsm_dispatch(&_nFInstance->sm, NULL); \
        } \
        ogs_sbi_nf_instance_remove(_nFInstance); \
    } while(0)
#define SEPP_SESS_CLEAR(__sESS) \
    do { \
        sepp_ue_t *sepp_ue = NULL; \
        ogs_assert(__sESS); \
        sepp_ue = __sESS->sepp_ue; \
        ogs_assert(sepp_ue); \
        if (SEPP_UE_IS_LAST_SESSION(sepp_ue)) \
            sepp_ue_remove(sepp_ue); \
        else \
            sepp_sess_remove(__sESS); \
    } while(0)

typedef struct sepp_sess_s sepp_sess_t;

typedef struct sepp_sess_s {
    ogs_sbi_object_t sbi;
    ogs_fsm_t       sm;             /* A state machine */

    uint64_t        smpolicycontrol_features; /* SBI features */

    /* S_NSSAI */
    ogs_s_nssai_t s_nssai;

    /* PDN Configuration */
    ogs_session_t session;

    sepp_ue_t *sepp_ue;
} sepp_sess_t;

void sepp_context_init(void);
void sepp_context_final(void);
sepp_context_t *sepp_self(void);

int sepp_context_parse_config(void);

sepp_ue_t *sepp_ue_add_by_supi(char *supi);
sepp_ue_t *sepp_ue_add_by_imsi(uint8_t *imsi, int imsi_len);
void sepp_ue_remove(sepp_ue_t *sepp_ue);
void sepp_ue_remove_all(void);
sepp_ue_t *sepp_ue_find_by_supi(char *supi);

void sepp_sess_remove(sepp_sess_t *sess);
void sepp_sess_remove_all(sepp_ue_t *sepp_ue);

sepp_sess_t *sepp_sess_find(uint32_t index);
sepp_sess_t *sepp_sess_find_by_ipv4(uint32_t addr);
sepp_sess_t *sepp_sess_find_by_ipv6(uint32_t *addr6);

void sepp_sess_select_nf(sepp_sess_t *sess, OpenAPI_nf_type_e nf_type);

#ifdef __cplusplus
}
#endif

#endif /* SEPP_CONTEXT_H */
