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

#ifndef SEPP_EVENT_H
#define SEPP_EVENT_H

#include "ogs-core.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sepp_sess_s sepp_sess_t;
typedef struct ogs_sbi_request_s ogs_sbi_request_t;
typedef struct ogs_sbi_response_s ogs_sbi_response_t;
typedef struct ogs_sbi_message_s ogs_sbi_message_t;
typedef struct ogs_sbi_subscription_s ogs_sbi_subscription_t;

typedef enum {
    SEPP_EVT_BASE = OGS_FSM_USER_SIG,

    SEPP_EVT_SBI_SERVER,
    SEPP_EVT_SBI_CLIENT,
    SEPP_EVT_SBI_TIMER,

    SEPP_EVT_TOP,

} sepp_event_e;

typedef struct sepp_event_s {
    int id;
    ogs_pkbuf_t *pkbuf;
    int timer_id;

    struct {
        ogs_sbi_request_t *request;
        ogs_sbi_response_t *response;
        void *data;
        int state;

        ogs_sbi_message_t *message;
    } sbi;

    sepp_sess_t *sess;
} sepp_event_t;

void sepp_event_init(void);
void sepp_event_final(void);

sepp_event_t *sepp_event_new(sepp_event_e id);
void sepp_event_free(sepp_event_t *e);

const char *sepp_event_get_name(sepp_event_t *e);

#ifdef __cplusplus
}
#endif

#endif /* SEPP_EVENT_H */
