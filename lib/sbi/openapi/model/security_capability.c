
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "security_capability.h"

OpenAPI_security_capability_t *OpenAPI_security_capability_create(
    )
{
    OpenAPI_security_capability_t *security_capability_local_var = OpenAPI_malloc(sizeof(OpenAPI_security_capability_t));
    if (!security_capability_local_var) {
        return NULL;
    }

    return security_capability_local_var;
}

void OpenAPI_security_capability_free(OpenAPI_security_capability_t *security_capability)
{
    if (NULL == security_capability) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(security_capability);
}

cJSON *OpenAPI_security_capability_convertToJSON(OpenAPI_security_capability_t *security_capability)
{
    cJSON *item = NULL;

    if (security_capability == NULL) {
        ogs_error("OpenAPI_security_capability_convertToJSON() failed [SecurityCapability]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_security_capability_t *OpenAPI_security_capability_parseFromJSON(cJSON *security_capabilityJSON)
{
    OpenAPI_security_capability_t *security_capability_local_var = NULL;
    security_capability_local_var = OpenAPI_security_capability_create (
        );

    return security_capability_local_var;
end:
    return NULL;
}

OpenAPI_security_capability_t *OpenAPI_security_capability_copy(OpenAPI_security_capability_t *dst, OpenAPI_security_capability_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_security_capability_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_security_capability_convertToJSON() failed");
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

    OpenAPI_security_capability_free(dst);
    dst = OpenAPI_security_capability_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

