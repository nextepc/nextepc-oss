
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ie_location.h"

OpenAPI_ie_location_t *OpenAPI_ie_location_create(
    )
{
    OpenAPI_ie_location_t *ie_location_local_var = OpenAPI_malloc(sizeof(OpenAPI_ie_location_t));
    if (!ie_location_local_var) {
        return NULL;
    }

    return ie_location_local_var;
}

void OpenAPI_ie_location_free(OpenAPI_ie_location_t *ie_location)
{
    if (NULL == ie_location) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(ie_location);
}

cJSON *OpenAPI_ie_location_convertToJSON(OpenAPI_ie_location_t *ie_location)
{
    cJSON *item = NULL;

    if (ie_location == NULL) {
        ogs_error("OpenAPI_ie_location_convertToJSON() failed [IeLocation]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_ie_location_t *OpenAPI_ie_location_parseFromJSON(cJSON *ie_locationJSON)
{
    OpenAPI_ie_location_t *ie_location_local_var = NULL;
    ie_location_local_var = OpenAPI_ie_location_create (
        );

    return ie_location_local_var;
end:
    return NULL;
}

OpenAPI_ie_location_t *OpenAPI_ie_location_copy(OpenAPI_ie_location_t *dst, OpenAPI_ie_location_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_ie_location_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_ie_location_convertToJSON() failed");
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

    OpenAPI_ie_location_free(dst);
    dst = OpenAPI_ie_location_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

