
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "failure_reason.h"

OpenAPI_failure_reason_t *OpenAPI_failure_reason_create(
    )
{
    OpenAPI_failure_reason_t *failure_reason_local_var = OpenAPI_malloc(sizeof(OpenAPI_failure_reason_t));
    if (!failure_reason_local_var) {
        return NULL;
    }

    return failure_reason_local_var;
}

void OpenAPI_failure_reason_free(OpenAPI_failure_reason_t *failure_reason)
{
    if (NULL == failure_reason) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(failure_reason);
}

cJSON *OpenAPI_failure_reason_convertToJSON(OpenAPI_failure_reason_t *failure_reason)
{
    cJSON *item = NULL;

    if (failure_reason == NULL) {
        ogs_error("OpenAPI_failure_reason_convertToJSON() failed [FailureReason]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_failure_reason_t *OpenAPI_failure_reason_parseFromJSON(cJSON *failure_reasonJSON)
{
    OpenAPI_failure_reason_t *failure_reason_local_var = NULL;
    failure_reason_local_var = OpenAPI_failure_reason_create (
        );

    return failure_reason_local_var;
end:
    return NULL;
}

OpenAPI_failure_reason_t *OpenAPI_failure_reason_copy(OpenAPI_failure_reason_t *dst, OpenAPI_failure_reason_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_failure_reason_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_failure_reason_convertToJSON() failed");
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

    OpenAPI_failure_reason_free(dst);
    dst = OpenAPI_failure_reason_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

