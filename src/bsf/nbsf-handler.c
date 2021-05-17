/*
 * Copyright (C) 2019,2020 by Sukchan Lee <acetcom@gmail.com>
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

#include "sbi-path.h"
#include "nbsf-handler.h"

bool bsf_nbsf_management_pcf_binding(
        bsf_sess_t *sess, ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
#if 0
    int rv, status = 0;
#else
    int status = 0;
#endif
    char *strerror = NULL;
    ogs_sbi_server_t *server = NULL;

    ogs_sbi_message_t sendmsg;
    ogs_sbi_header_t header;
    ogs_sbi_response_t *response = NULL;

    OpenAPI_pcf_binding_t *PcfBinding = NULL;
    uint64_t supported_features = 0;

    ogs_assert(stream);
    ogs_assert(recvmsg);
    server = ogs_sbi_server_from_stream(stream);
    ogs_assert(server);

    if (recvmsg->h.resource.component[1]) {
        SWITCH(recvmsg->h.method)
        CASE(OGS_SBI_HTTP_METHOD_DELETE)
            ogs_fatal("DELETE");
            break;

        CASE(OGS_SBI_HTTP_METHOD_PATCH)
            break;

        DEFAULT
            strerror = ogs_msprintf("Invalid HTTP method [%s]",
                    recvmsg->h.method);
            status = OGS_SBI_HTTP_STATUS_BAD_REQUEST;
            goto cleanup;
        END
    } else {
        SWITCH(recvmsg->h.method)
        CASE(OGS_SBI_HTTP_METHOD_POST)

            memset(&header, 0, sizeof(header));
            header.service.name =
                (char *)OGS_SBI_SERVICE_NAME_NBSF_MANAGEMENT;
            header.api.version = (char *)OGS_SBI_API_V1;
            header.resource.component[0] =
                (char *)OGS_SBI_RESOURCE_NAME_PCF_BINDINGS;
            header.resource.component[1] = sess->binding_id;

            PcfBinding = recvmsg->PcfBinding;
            ogs_assert(PcfBinding);

            if (PcfBinding->supp_feat) {
                supported_features =
                    ogs_uint64_from_string(PcfBinding->supp_feat);
                sess->management_features &= supported_features;
            } else {
                sess->management_features = 0;
            }

            memset(&sendmsg, 0, sizeof(sendmsg));
            sendmsg.PcfBinding = recvmsg->PcfBinding;
            sendmsg.http.location = ogs_sbi_server_uri(server, &header);

            response = ogs_sbi_build_response(
                    &sendmsg, OGS_SBI_HTTP_STATUS_CREATED);
            ogs_assert(response);
            ogs_sbi_server_send_response(stream, response);

            ogs_free(sendmsg.http.location);
            break;

        DEFAULT
            strerror = ogs_msprintf("Invalid HTTP method [%s]",
                    recvmsg->h.method);
            status = OGS_SBI_HTTP_STATUS_BAD_REQUEST;
            goto cleanup;
        END
    }

    return true;

cleanup:
    ogs_assert(strerror);
    ogs_assert(status);
    ogs_error("%s", strerror);
    ogs_sbi_server_send_error(stream, status, recvmsg, strerror, NULL);
    ogs_free(strerror);

    return false;
}
