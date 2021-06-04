
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http_header.h"

OpenAPI_http_header_t *OpenAPI_http_header_create(
    char *header,
    OpenAPI_encoded_http_header_value_t *value
    )
{
    OpenAPI_http_header_t *http_header_local_var = OpenAPI_malloc(sizeof(OpenAPI_http_header_t));
    if (!http_header_local_var) {
        return NULL;
    }
    http_header_local_var->header = header;
    http_header_local_var->value = value;

    return http_header_local_var;
}

void OpenAPI_http_header_free(OpenAPI_http_header_t *http_header)
{
    if (NULL == http_header) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(http_header->header);
    OpenAPI_encoded_http_header_value_free(http_header->value);
    ogs_free(http_header);
}

cJSON *OpenAPI_http_header_convertToJSON(OpenAPI_http_header_t *http_header)
{
    cJSON *item = NULL;

    if (http_header == NULL) {
        ogs_error("OpenAPI_http_header_convertToJSON() failed [HttpHeader]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "header", http_header->header) == NULL) {
        ogs_error("OpenAPI_http_header_convertToJSON() failed [header]");
        goto end;
    }

    cJSON *value_local_JSON = OpenAPI_encoded_http_header_value_convertToJSON(http_header->value);
    if (value_local_JSON == NULL) {
        ogs_error("OpenAPI_http_header_convertToJSON() failed [value]");
        goto end;
    }
    cJSON_AddItemToObject(item, "value", value_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_http_header_convertToJSON() failed [value]");
        goto end;
    }

end:
    return item;
}

OpenAPI_http_header_t *OpenAPI_http_header_parseFromJSON(cJSON *http_headerJSON)
{
    OpenAPI_http_header_t *http_header_local_var = NULL;
    cJSON *header = cJSON_GetObjectItemCaseSensitive(http_headerJSON, "header");
    if (!header) {
        ogs_error("OpenAPI_http_header_parseFromJSON() failed [header]");
        goto end;
    }


    if (!cJSON_IsString(header)) {
        ogs_error("OpenAPI_http_header_parseFromJSON() failed [header]");
        goto end;
    }

    cJSON *value = cJSON_GetObjectItemCaseSensitive(http_headerJSON, "value");
    if (!value) {
        ogs_error("OpenAPI_http_header_parseFromJSON() failed [value]");
        goto end;
    }

    OpenAPI_encoded_http_header_value_t *value_local_nonprim = NULL;

    value_local_nonprim = OpenAPI_encoded_http_header_value_parseFromJSON(value);

    http_header_local_var = OpenAPI_http_header_create (
        ogs_strdup(header->valuestring),
        value_local_nonprim
        );

    return http_header_local_var;
end:
    return NULL;
}

OpenAPI_http_header_t *OpenAPI_http_header_copy(OpenAPI_http_header_t *dst, OpenAPI_http_header_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_http_header_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_http_header_convertToJSON() failed");
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

    OpenAPI_http_header_free(dst);
    dst = OpenAPI_http_header_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

