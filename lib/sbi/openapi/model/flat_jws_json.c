
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "flat_jws_json.h"

OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_create(
    char *payload,
    char *protected,
    OpenAPI_object_t *header,
    char *signature
    )
{
    OpenAPI_flat_jws_json_t *flat_jws_json_local_var = OpenAPI_malloc(sizeof(OpenAPI_flat_jws_json_t));
    if (!flat_jws_json_local_var) {
        return NULL;
    }
    flat_jws_json_local_var->payload = payload;
    flat_jws_json_local_var->protected = protected;
    flat_jws_json_local_var->header = header;
    flat_jws_json_local_var->signature = signature;

    return flat_jws_json_local_var;
}

void OpenAPI_flat_jws_json_free(OpenAPI_flat_jws_json_t *flat_jws_json)
{
    if (NULL == flat_jws_json) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(flat_jws_json->payload);
    ogs_free(flat_jws_json->protected);
    OpenAPI_object_free(flat_jws_json->header);
    ogs_free(flat_jws_json->signature);
    ogs_free(flat_jws_json);
}

cJSON *OpenAPI_flat_jws_json_convertToJSON(OpenAPI_flat_jws_json_t *flat_jws_json)
{
    cJSON *item = NULL;

    if (flat_jws_json == NULL) {
        ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [FlatJwsJson]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "payload", flat_jws_json->payload) == NULL) {
        ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [payload]");
        goto end;
    }

    if (flat_jws_json->protected) {
        if (cJSON_AddStringToObject(item, "protected", flat_jws_json->protected) == NULL) {
            ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [protected]");
            goto end;
        }
    }

    if (flat_jws_json->header) {
        cJSON *header_object = OpenAPI_object_convertToJSON(flat_jws_json->header);
        if (header_object == NULL) {
            ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [header]");
            goto end;
        }
        cJSON_AddItemToObject(item, "header", header_object);
        if (item->child == NULL) {
            ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [header]");
            goto end;
        }
    }

    if (cJSON_AddStringToObject(item, "signature", flat_jws_json->signature) == NULL) {
        ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed [signature]");
        goto end;
    }

end:
    return item;
}

OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_parseFromJSON(cJSON *flat_jws_jsonJSON)
{
    OpenAPI_flat_jws_json_t *flat_jws_json_local_var = NULL;
    cJSON *payload = cJSON_GetObjectItemCaseSensitive(flat_jws_jsonJSON, "payload");
    if (!payload) {
        ogs_error("OpenAPI_flat_jws_json_parseFromJSON() failed [payload]");
        goto end;
    }


    if (!cJSON_IsString(payload)) {
        ogs_error("OpenAPI_flat_jws_json_parseFromJSON() failed [payload]");
        goto end;
    }

    cJSON *protected = cJSON_GetObjectItemCaseSensitive(flat_jws_jsonJSON, "protected");

    if (protected) {
        if (!cJSON_IsString(protected)) {
            ogs_error("OpenAPI_flat_jws_json_parseFromJSON() failed [protected]");
            goto end;
        }
    }

    cJSON *header = cJSON_GetObjectItemCaseSensitive(flat_jws_jsonJSON, "header");

    OpenAPI_object_t *header_local_object = NULL;
    if (header) {
        header_local_object = OpenAPI_object_parseFromJSON(header);
    }

    cJSON *signature = cJSON_GetObjectItemCaseSensitive(flat_jws_jsonJSON, "signature");
    if (!signature) {
        ogs_error("OpenAPI_flat_jws_json_parseFromJSON() failed [signature]");
        goto end;
    }


    if (!cJSON_IsString(signature)) {
        ogs_error("OpenAPI_flat_jws_json_parseFromJSON() failed [signature]");
        goto end;
    }

    flat_jws_json_local_var = OpenAPI_flat_jws_json_create (
        ogs_strdup(payload->valuestring),
        protected ? ogs_strdup(protected->valuestring) : NULL,
        header ? header_local_object : NULL,
        ogs_strdup(signature->valuestring)
        );

    return flat_jws_json_local_var;
end:
    return NULL;
}

OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_copy(OpenAPI_flat_jws_json_t *dst, OpenAPI_flat_jws_json_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_flat_jws_json_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_flat_jws_json_convertToJSON() failed");
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

    OpenAPI_flat_jws_json_free(dst);
    dst = OpenAPI_flat_jws_json_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

