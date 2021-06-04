
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http_payload.h"

OpenAPI_http_payload_t *OpenAPI_http_payload_create(
    char *ie_path,
    OpenAPI_ie_location_e ie_value_location,
    OpenAPI_object_t *value
    )
{
    OpenAPI_http_payload_t *http_payload_local_var = OpenAPI_malloc(sizeof(OpenAPI_http_payload_t));
    if (!http_payload_local_var) {
        return NULL;
    }
    http_payload_local_var->ie_path = ie_path;
    http_payload_local_var->ie_value_location = ie_value_location;
    http_payload_local_var->value = value;

    return http_payload_local_var;
}

void OpenAPI_http_payload_free(OpenAPI_http_payload_t *http_payload)
{
    if (NULL == http_payload) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(http_payload->ie_path);
    OpenAPI_object_free(http_payload->value);
    ogs_free(http_payload);
}

cJSON *OpenAPI_http_payload_convertToJSON(OpenAPI_http_payload_t *http_payload)
{
    cJSON *item = NULL;

    if (http_payload == NULL) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed [HttpPayload]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "iePath", http_payload->ie_path) == NULL) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed [ie_path]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "ieValueLocation", OpenAPI_ie_location_ToString(http_payload->ie_value_location)) == NULL) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed [ie_value_location]");
        goto end;
    }

    cJSON *value_object = OpenAPI_object_convertToJSON(http_payload->value);
    if (value_object == NULL) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed [value]");
        goto end;
    }
    cJSON_AddItemToObject(item, "value", value_object);
    if (item->child == NULL) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed [value]");
        goto end;
    }

end:
    return item;
}

OpenAPI_http_payload_t *OpenAPI_http_payload_parseFromJSON(cJSON *http_payloadJSON)
{
    OpenAPI_http_payload_t *http_payload_local_var = NULL;
    cJSON *ie_path = cJSON_GetObjectItemCaseSensitive(http_payloadJSON, "iePath");
    if (!ie_path) {
        ogs_error("OpenAPI_http_payload_parseFromJSON() failed [ie_path]");
        goto end;
    }


    if (!cJSON_IsString(ie_path)) {
        ogs_error("OpenAPI_http_payload_parseFromJSON() failed [ie_path]");
        goto end;
    }

    cJSON *ie_value_location = cJSON_GetObjectItemCaseSensitive(http_payloadJSON, "ieValueLocation");
    if (!ie_value_location) {
        ogs_error("OpenAPI_http_payload_parseFromJSON() failed [ie_value_location]");
        goto end;
    }

    OpenAPI_ie_location_e ie_value_locationVariable;

    if (!cJSON_IsString(ie_value_location)) {
        ogs_error("OpenAPI_http_payload_parseFromJSON() failed [ie_value_location]");
        goto end;
    }
    ie_value_locationVariable = OpenAPI_ie_location_FromString(ie_value_location->valuestring);

    cJSON *value = cJSON_GetObjectItemCaseSensitive(http_payloadJSON, "value");
    if (!value) {
        ogs_error("OpenAPI_http_payload_parseFromJSON() failed [value]");
        goto end;
    }

    OpenAPI_object_t *value_local_object = NULL;

    value_local_object = OpenAPI_object_parseFromJSON(value);

    http_payload_local_var = OpenAPI_http_payload_create (
        ogs_strdup(ie_path->valuestring),
        ie_value_locationVariable,
        value_local_object
        );

    return http_payload_local_var;
end:
    return NULL;
}

OpenAPI_http_payload_t *OpenAPI_http_payload_copy(OpenAPI_http_payload_t *dst, OpenAPI_http_payload_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_http_payload_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_http_payload_convertToJSON() failed");
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

    OpenAPI_http_payload_free(dst);
    dst = OpenAPI_http_payload_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

