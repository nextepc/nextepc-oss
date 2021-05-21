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

bool bsf_nbsf_management_handle_pcf_binding(
        bsf_sess_t *sess, ogs_sbi_stream_t *stream, ogs_sbi_message_t *recvmsg)
{
    int status = 0;
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
            memset(&sendmsg, 0, sizeof(sendmsg));

            response = ogs_sbi_build_response(
                    &sendmsg, OGS_SBI_HTTP_STATUS_NO_CONTENT);
            ogs_assert(response);
            ogs_sbi_server_send_response(stream, response);

            ogs_free(sendmsg.http.location);

            bsf_sess_remove(sess);
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
        OpenAPI_list_t *PcfIpEndPointList = NULL;
        OpenAPI_lnode_t *node = NULL;
        int i, rv;

        SWITCH(recvmsg->h.method)
        CASE(OGS_SBI_HTTP_METHOD_POST)

            PcfBinding = recvmsg->PcfBinding;
            ogs_assert(PcfBinding);

            if (!PcfBinding->ipv4_addr && !PcfBinding->ipv6_prefix) {
                strerror = ogs_msprintf(
                            "No IPv4 address or IPv6 prefix[%p:%p]",
                            PcfBinding->ipv4_addr, PcfBinding->ipv6_prefix);
                status = OGS_SBI_HTTP_STATUS_BAD_REQUEST;
                goto cleanup;
            }

            if (!PcfBinding->pcf_fqdn && !PcfBinding->pcf_ip_end_points) {
                strerror = ogs_msprintf("No PCF address information [%p:%p]",
                            PcfBinding->pcf_fqdn,
                            PcfBinding->pcf_ip_end_points);
                status = OGS_SBI_HTTP_STATUS_BAD_REQUEST;
                goto cleanup;
            }

            if (PcfBinding->ipv4_addr)
                bsf_sess_set_ipv4addr(sess, PcfBinding->ipv4_addr);
            if (PcfBinding->ipv6_prefix)
                bsf_sess_set_ipv6prefix(sess, PcfBinding->ipv6_prefix);

            if (PcfBinding->pcf_fqdn) {
                char fqdn[OGS_MAX_FQDN_LEN];

                ogs_fqdn_parse(fqdn,
                        PcfBinding->pcf_fqdn, strlen(PcfBinding->pcf_fqdn));

                if (sess->pcf_fqdn)
                    ogs_free(sess->pcf_fqdn);
                sess->pcf_fqdn = ogs_strdup(fqdn);
            }

            PcfIpEndPointList = PcfBinding->pcf_ip_end_points;

            for (i = 0; i < sess->num_of_addr; i++) {
                if (sess->addr[i].ipv4)
                    ogs_freeaddrinfo(sess->addr[i].ipv4);
                if (sess->addr[i].ipv6)
                    ogs_freeaddrinfo(sess->addr[i].ipv6);
            }
            sess->num_of_addr = 0;

            OpenAPI_list_for_each(PcfIpEndPointList, node) {
                OpenAPI_ip_end_point_t *IpEndPoint = node->data;
                ogs_sockaddr_t *addr = NULL, *addr6 = NULL;
                int port = 0;

                if (!IpEndPoint) continue;

                if (sess->num_of_addr < OGS_SBI_MAX_NUM_OF_IP_ADDRESS) {
                    port = IpEndPoint->port;
                    if (!port) {
                        if (ogs_sbi_default_uri_scheme() ==
                                OpenAPI_uri_scheme_http)
                            port = OGS_SBI_HTTP_PORT;
                        else if (ogs_sbi_default_uri_scheme() ==
                                OpenAPI_uri_scheme_https)
                            port = OGS_SBI_HTTPS_PORT;
                        else {
                            ogs_fatal("Invalid scheme [%d]",
                                ogs_sbi_default_uri_scheme());
                            ogs_assert_if_reached();
                        }
                    }

                    if (IpEndPoint->ipv4_address) {
                        rv = ogs_getaddrinfo(&addr, AF_UNSPEC,
                                IpEndPoint->ipv4_address, port, 0);
                        if (rv != OGS_OK) continue;
                    }
                    if (IpEndPoint->ipv6_address) {
                        rv = ogs_getaddrinfo(&addr6, AF_UNSPEC,
                                IpEndPoint->ipv6_address, port, 0);
                        if (rv != OGS_OK) continue;
                    }

                    if (addr || addr6) {
                        sess->addr[sess->num_of_addr].port = port;
                        sess->addr[sess->num_of_addr].ipv4 = addr;
                        sess->addr[sess->num_of_addr].ipv6 = addr6;
                        sess->num_of_addr++;
                    }
                }
            }

            if (PcfBinding->supi) {
                if (sess->supi)
                    ogs_free(sess->supi);
                sess->supi = ogs_strdup(PcfBinding->supi);
            }
            if (PcfBinding->gpsi) {
                if (sess->gpsi)
                    ogs_free(sess->gpsi);
                sess->gpsi = ogs_strdup(PcfBinding->gpsi);
            }

            memset(&header, 0, sizeof(header));
            header.service.name =
                (char *)OGS_SBI_SERVICE_NAME_NBSF_MANAGEMENT;
            header.api.version = (char *)OGS_SBI_API_V1;
            header.resource.component[0] =
                (char *)OGS_SBI_RESOURCE_NAME_PCF_BINDINGS;
            header.resource.component[1] = sess->binding_id;

            if (PcfBinding->supp_feat) {
                supported_features =
                    ogs_uint64_from_string(PcfBinding->supp_feat);
                sess->management_features &= supported_features;
            } else {
                sess->management_features = 0;
            }

            memset(&sendmsg, 0, sizeof(sendmsg));
            sendmsg.PcfBinding = PcfBinding;
            sendmsg.http.location = ogs_sbi_server_uri(server, &header);

            response = ogs_sbi_build_response(
                    &sendmsg, OGS_SBI_HTTP_STATUS_CREATED);
            ogs_assert(response);
            ogs_sbi_server_send_response(stream, response);

            ogs_free(sendmsg.http.location);
            break;

        CASE(OGS_SBI_HTTP_METHOD_POST)
            memset(&sendmsg, 0, sizeof(sendmsg));
            sendmsg.PcfBinding = PcfBinding;

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
