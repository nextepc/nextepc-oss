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

#include "npcf-build.h"

ogs_sbi_request_t *af_npcf_policyauthorization_build_create(
        af_sess_t *sess, void *data)
{
    ogs_sbi_message_t message;
    ogs_sbi_request_t *request = NULL;
    ogs_sbi_server_t *server = NULL;
    ogs_sbi_header_t header;

    OpenAPI_app_session_context_t AppSessionContext;
    OpenAPI_app_session_context_req_data_t AscReqData;
    OpenAPI_snssai_t sNssai;

    OpenAPI_list_t *MediaComponentList = NULL;
    OpenAPI_map_t *MediaComponentMap = NULL;
    OpenAPI_media_component_t *MediaComponent = NULL;

    OpenAPI_list_t *SubComponentList = NULL;
    OpenAPI_map_t *SubComponentMap = NULL;
    OpenAPI_media_sub_component_t *SubComponent = NULL;

    int i, j;
    OpenAPI_lnode_t *node = NULL, *node2 = NULL;

    ogs_assert(sess);
    ogs_assert(sess->af_app_session_id);

    memset(&message, 0, sizeof(message));
    message.h.method = (char *)OGS_SBI_HTTP_METHOD_POST;
    message.h.service.name =
        (char *)OGS_SBI_SERVICE_NAME_NPCF_POLICYAUTHORIZATION;
    message.h.api.version = (char *)OGS_SBI_API_V1;
    message.h.resource.component[0] =
        (char *)OGS_SBI_RESOURCE_NAME_APP_SESSIONS;

    message.AppSessionContext = &AppSessionContext;

    memset(&AppSessionContext, 0, sizeof(AppSessionContext));
    AppSessionContext.asc_req_data = &AscReqData;

    memset(&AscReqData, 0, sizeof(AscReqData));

    server = ogs_list_first(&ogs_sbi_self()->server_list);
    ogs_assert(server);

    memset(&header, 0, sizeof(header));
    header.service.name = (char *)OGS_SBI_SERVICE_NAME_NPCF_POLICYAUTHORIZATION;
    header.api.version = (char *)OGS_SBI_API_V1;
    header.resource.component[0] = (char *)OGS_SBI_RESOURCE_NAME_APP_SESSIONS;
    header.resource.component[1] = (char *)sess->af_app_session_id;
    header.resource.component[2] = (char *)OGS_SBI_RESOURCE_NAME_NOTIFY;
    AscReqData.notif_uri = ogs_sbi_server_uri(server, &header);
    ogs_assert(AscReqData.notif_uri);

    AscReqData.supp_feat =
        ogs_uint64_to_string(sess->policyauthorization_features);
    ogs_assert(AscReqData.supp_feat);

    AscReqData.ue_ipv4 = sess->ipv4addr;
    AscReqData.ue_ipv6 = sess->ipv6addr;

    AscReqData.dnn = sess->dnn;

    memset(&sNssai, 0, sizeof(sNssai));
    if (sess->s_nssai.sst) {
        sNssai.sst = sess->s_nssai.sst;
        sNssai.sd = ogs_s_nssai_sd_to_string(sess->s_nssai.sd);
        AscReqData.slice_info = &sNssai;
    }

    AscReqData.supi = sess->supi;
    AscReqData.gpsi = sess->gpsi;

    /* Media Component */
    i = 0, j = 0;

    MediaComponentList = OpenAPI_list_create();
    ogs_assert(MediaComponentList);

    MediaComponent = ogs_calloc(1, sizeof(*MediaComponent));
    ogs_assert(MediaComponent);

    MediaComponent->med_comp_n = (++i);

    MediaComponentMap = OpenAPI_map_create(
            ogs_msprintf("%d", MediaComponent->med_comp_n), MediaComponent);
    ogs_assert(MediaComponentMap);

    OpenAPI_list_add(MediaComponentList, MediaComponentMap);

    ogs_assert(MediaComponentList->count);
    AscReqData.med_components = MediaComponentList;

    SubComponentList = OpenAPI_list_create();
    ogs_assert(SubComponentList);

    /* Sub Component #1 */
    SubComponent = ogs_calloc(1, sizeof(*SubComponent));
    ogs_assert(SubComponent);

    SubComponent->f_num = (++j);

    SubComponentMap = OpenAPI_map_create(
            ogs_msprintf("%d", SubComponent->f_num), SubComponent);
    ogs_assert(SubComponentMap);

    OpenAPI_list_add(SubComponentList, SubComponentMap);

    /* Sub Component #2 */
    SubComponent = ogs_calloc(1, sizeof(*SubComponent));
    ogs_assert(SubComponent);

    SubComponent->f_num = (++j);

    SubComponentMap = OpenAPI_map_create(
            ogs_msprintf("%d", SubComponent->f_num), SubComponent);
    ogs_assert(SubComponentMap);

    OpenAPI_list_add(SubComponentList, SubComponentMap);

    ogs_assert(SubComponentList->count);
    MediaComponent->med_sub_comps = SubComponentList;

    request = ogs_sbi_build_request(&message);
    ogs_assert(request);

    ogs_free(AscReqData.notif_uri);

    ogs_free(AscReqData.supp_feat);

    if (sNssai.sd)
        ogs_free(sNssai.sd);

    MediaComponentList = AscReqData.med_components;
    OpenAPI_list_for_each(MediaComponentList, node) {
        MediaComponentMap = node->data;
        if (MediaComponentMap) {
            MediaComponent = MediaComponentMap->value;
            if (MediaComponent) {

                SubComponentList = MediaComponent->med_sub_comps;
                OpenAPI_list_for_each(SubComponentList, node2) {
                    SubComponentMap = node2->data;
                    if (SubComponentMap) {
                        SubComponent = SubComponentMap->value;
                        if (SubComponent) {
                            ogs_free(SubComponent);
                        }
                        if (SubComponentMap->key)
                            ogs_free(SubComponentMap->key);
                        ogs_free(SubComponentMap);
                    }
                }
                OpenAPI_list_free(SubComponentList);

                ogs_free(MediaComponent);
            }
            if (MediaComponentMap->key)
                ogs_free(MediaComponentMap->key);
            ogs_free(MediaComponentMap);
        }
    }
    OpenAPI_list_free(MediaComponentList);

    return request;
}
