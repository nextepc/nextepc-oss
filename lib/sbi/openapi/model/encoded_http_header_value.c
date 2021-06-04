
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "encoded_http_header_value.h"

OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_create(
    int enc_block_index
    )
{
    OpenAPI_encoded_http_header_value_t *encoded_http_header_value_local_var = OpenAPI_malloc(sizeof(OpenAPI_encoded_http_header_value_t));
    if (!encoded_http_header_value_local_var) {
        return NULL;
    }
    encoded_http_header_value_local_var->enc_block_index = enc_block_index;

    return encoded_http_header_value_local_var;
}

void OpenAPI_encoded_http_header_value_free(OpenAPI_encoded_http_header_value_t *encoded_http_header_value)
{
    if (NULL == encoded_http_header_value) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(encoded_http_header_value);
}

cJSON *OpenAPI_encoded_http_header_value_convertToJSON(OpenAPI_encoded_http_header_value_t *encoded_http_header_value)
{
    cJSON *item = NULL;

    if (encoded_http_header_value == NULL) {
        ogs_error("OpenAPI_encoded_http_header_value_convertToJSON() failed [EncodedHttpHeaderValue]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddNumberToObject(item, "encBlockIndex", encoded_http_header_value->enc_block_index) == NULL) {
        ogs_error("OpenAPI_encoded_http_header_value_convertToJSON() failed [enc_block_index]");
        goto end;
    }

end:
    return item;
}

OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_parseFromJSON(cJSON *encoded_http_header_valueJSON)
{
    OpenAPI_encoded_http_header_value_t *encoded_http_header_value_local_var = NULL;
    cJSON *enc_block_index = cJSON_GetObjectItemCaseSensitive(encoded_http_header_valueJSON, "encBlockIndex");
    if (!enc_block_index) {
        ogs_error("OpenAPI_encoded_http_header_value_parseFromJSON() failed [enc_block_index]");
        goto end;
    }


    if (!cJSON_IsNumber(enc_block_index)) {
        ogs_error("OpenAPI_encoded_http_header_value_parseFromJSON() failed [enc_block_index]");
        goto end;
    }

    encoded_http_header_value_local_var = OpenAPI_encoded_http_header_value_create (
        enc_block_index->valuedouble
        );

    return encoded_http_header_value_local_var;
end:
    return NULL;
}

OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_copy(OpenAPI_encoded_http_header_value_t *dst, OpenAPI_encoded_http_header_value_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_encoded_http_header_value_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_encoded_http_header_value_convertToJSON() failed");
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

    OpenAPI_encoded_http_header_value_free(dst);
    dst = OpenAPI_encoded_http_header_value_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

