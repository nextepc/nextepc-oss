
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_to_integrity_protect_block.h"

OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_create(
    OpenAPI_meta_data_t *meta_data,
    OpenAPI_request_line_t *request_line,
    char *status_line,
    OpenAPI_list_t *headers,
    OpenAPI_list_t *payload
    )
{
    OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block_local_var = OpenAPI_malloc(sizeof(OpenAPI_data_to_integrity_protect_block_t));
    if (!data_to_integrity_protect_block_local_var) {
        return NULL;
    }
    data_to_integrity_protect_block_local_var->meta_data = meta_data;
    data_to_integrity_protect_block_local_var->request_line = request_line;
    data_to_integrity_protect_block_local_var->status_line = status_line;
    data_to_integrity_protect_block_local_var->headers = headers;
    data_to_integrity_protect_block_local_var->payload = payload;

    return data_to_integrity_protect_block_local_var;
}

void OpenAPI_data_to_integrity_protect_block_free(OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block)
{
    if (NULL == data_to_integrity_protect_block) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_meta_data_free(data_to_integrity_protect_block->meta_data);
    OpenAPI_request_line_free(data_to_integrity_protect_block->request_line);
    ogs_free(data_to_integrity_protect_block->status_line);
    OpenAPI_list_for_each(data_to_integrity_protect_block->headers, node) {
        OpenAPI_http_header_free(node->data);
    }
    OpenAPI_list_free(data_to_integrity_protect_block->headers);
    OpenAPI_list_for_each(data_to_integrity_protect_block->payload, node) {
        OpenAPI_http_payload_free(node->data);
    }
    OpenAPI_list_free(data_to_integrity_protect_block->payload);
    ogs_free(data_to_integrity_protect_block);
}

cJSON *OpenAPI_data_to_integrity_protect_block_convertToJSON(OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block)
{
    cJSON *item = NULL;

    if (data_to_integrity_protect_block == NULL) {
        ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [DataToIntegrityProtectBlock]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (data_to_integrity_protect_block->meta_data) {
        cJSON *meta_data_local_JSON = OpenAPI_meta_data_convertToJSON(data_to_integrity_protect_block->meta_data);
        if (meta_data_local_JSON == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [meta_data]");
            goto end;
        }
        cJSON_AddItemToObject(item, "metaData", meta_data_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [meta_data]");
            goto end;
        }
    }

    if (data_to_integrity_protect_block->request_line) {
        cJSON *request_line_local_JSON = OpenAPI_request_line_convertToJSON(data_to_integrity_protect_block->request_line);
        if (request_line_local_JSON == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [request_line]");
            goto end;
        }
        cJSON_AddItemToObject(item, "requestLine", request_line_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [request_line]");
            goto end;
        }
    }

    if (data_to_integrity_protect_block->status_line) {
        if (cJSON_AddStringToObject(item, "statusLine", data_to_integrity_protect_block->status_line) == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [status_line]");
            goto end;
        }
    }

    if (data_to_integrity_protect_block->headers) {
        cJSON *headersList = cJSON_AddArrayToObject(item, "headers");
        if (headersList == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [headers]");
            goto end;
        }

        OpenAPI_lnode_t *headers_node;
        if (data_to_integrity_protect_block->headers) {
            OpenAPI_list_for_each(data_to_integrity_protect_block->headers, headers_node) {
                cJSON *itemLocal = OpenAPI_http_header_convertToJSON(headers_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [headers]");
                    goto end;
                }
                cJSON_AddItemToArray(headersList, itemLocal);
            }
        }
    }

    if (data_to_integrity_protect_block->payload) {
        cJSON *payloadList = cJSON_AddArrayToObject(item, "payload");
        if (payloadList == NULL) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [payload]");
            goto end;
        }

        OpenAPI_lnode_t *payload_node;
        if (data_to_integrity_protect_block->payload) {
            OpenAPI_list_for_each(data_to_integrity_protect_block->payload, payload_node) {
                cJSON *itemLocal = OpenAPI_http_payload_convertToJSON(payload_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed [payload]");
                    goto end;
                }
                cJSON_AddItemToArray(payloadList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_parseFromJSON(cJSON *data_to_integrity_protect_blockJSON)
{
    OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block_local_var = NULL;
    cJSON *meta_data = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_blockJSON, "metaData");

    OpenAPI_meta_data_t *meta_data_local_nonprim = NULL;
    if (meta_data) {
        meta_data_local_nonprim = OpenAPI_meta_data_parseFromJSON(meta_data);
    }

    cJSON *request_line = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_blockJSON, "requestLine");

    OpenAPI_request_line_t *request_line_local_nonprim = NULL;
    if (request_line) {
        request_line_local_nonprim = OpenAPI_request_line_parseFromJSON(request_line);
    }

    cJSON *status_line = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_blockJSON, "statusLine");

    if (status_line) {
        if (!cJSON_IsString(status_line)) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_parseFromJSON() failed [status_line]");
            goto end;
        }
    }

    cJSON *headers = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_blockJSON, "headers");

    OpenAPI_list_t *headersList;
    if (headers) {
        cJSON *headers_local_nonprimitive;
        if (!cJSON_IsArray(headers)) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_parseFromJSON() failed [headers]");
            goto end;
        }

        headersList = OpenAPI_list_create();

        cJSON_ArrayForEach(headers_local_nonprimitive, headers ) {
            if (!cJSON_IsObject(headers_local_nonprimitive)) {
                ogs_error("OpenAPI_data_to_integrity_protect_block_parseFromJSON() failed [headers]");
                goto end;
            }
            OpenAPI_http_header_t *headersItem = OpenAPI_http_header_parseFromJSON(headers_local_nonprimitive);

            OpenAPI_list_add(headersList, headersItem);
        }
    }

    cJSON *payload = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_blockJSON, "payload");

    OpenAPI_list_t *payloadList;
    if (payload) {
        cJSON *payload_local_nonprimitive;
        if (!cJSON_IsArray(payload)) {
            ogs_error("OpenAPI_data_to_integrity_protect_block_parseFromJSON() failed [payload]");
            goto end;
        }

        payloadList = OpenAPI_list_create();

        cJSON_ArrayForEach(payload_local_nonprimitive, payload ) {
            if (!cJSON_IsObject(payload_local_nonprimitive)) {
                ogs_error("OpenAPI_data_to_integrity_protect_block_parseFromJSON() failed [payload]");
                goto end;
            }
            OpenAPI_http_payload_t *payloadItem = OpenAPI_http_payload_parseFromJSON(payload_local_nonprimitive);

            OpenAPI_list_add(payloadList, payloadItem);
        }
    }

    data_to_integrity_protect_block_local_var = OpenAPI_data_to_integrity_protect_block_create (
        meta_data ? meta_data_local_nonprim : NULL,
        request_line ? request_line_local_nonprim : NULL,
        status_line ? ogs_strdup(status_line->valuestring) : NULL,
        headers ? headersList : NULL,
        payload ? payloadList : NULL
        );

    return data_to_integrity_protect_block_local_var;
end:
    return NULL;
}

OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_copy(OpenAPI_data_to_integrity_protect_block_t *dst, OpenAPI_data_to_integrity_protect_block_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_data_to_integrity_protect_block_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_data_to_integrity_protect_block_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_data_to_integrity_protect_block_free(dst);
    dst = OpenAPI_data_to_integrity_protect_block_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

