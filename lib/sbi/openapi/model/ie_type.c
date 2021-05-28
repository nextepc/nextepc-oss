
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ie_type.h"

OpenAPI_ie_type_t *OpenAPI_ie_type_create(
    )
{
    OpenAPI_ie_type_t *ie_type_local_var = OpenAPI_malloc(sizeof(OpenAPI_ie_type_t));
    if (!ie_type_local_var) {
        return NULL;
    }

    return ie_type_local_var;
}

void OpenAPI_ie_type_free(OpenAPI_ie_type_t *ie_type)
{
    if (NULL == ie_type) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(ie_type);
}

cJSON *OpenAPI_ie_type_convertToJSON(OpenAPI_ie_type_t *ie_type)
{
    cJSON *item = NULL;

    if (ie_type == NULL) {
        ogs_error("OpenAPI_ie_type_convertToJSON() failed [IeType]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_ie_type_t *OpenAPI_ie_type_parseFromJSON(cJSON *ie_typeJSON)
{
    OpenAPI_ie_type_t *ie_type_local_var = NULL;
    ie_type_local_var = OpenAPI_ie_type_create (
        );

    return ie_type_local_var;
end:
    return NULL;
}

OpenAPI_ie_type_t *OpenAPI_ie_type_copy(OpenAPI_ie_type_t *dst, OpenAPI_ie_type_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_ie_type_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_ie_type_convertToJSON() failed");
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

    OpenAPI_ie_type_free(dst);
    dst = OpenAPI_ie_type_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

