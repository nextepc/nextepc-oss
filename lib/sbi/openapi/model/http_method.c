
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http_method.h"

OpenAPI_http_method_t *OpenAPI_http_method_create(
    )
{
    OpenAPI_http_method_t *http_method_local_var = OpenAPI_malloc(sizeof(OpenAPI_http_method_t));
    if (!http_method_local_var) {
        return NULL;
    }

    return http_method_local_var;
}

void OpenAPI_http_method_free(OpenAPI_http_method_t *http_method)
{
    if (NULL == http_method) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(http_method);
}

cJSON *OpenAPI_http_method_convertToJSON(OpenAPI_http_method_t *http_method)
{
    cJSON *item = NULL;

    if (http_method == NULL) {
        ogs_error("OpenAPI_http_method_convertToJSON() failed [HttpMethod]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_http_method_t *OpenAPI_http_method_parseFromJSON(cJSON *http_methodJSON)
{
    OpenAPI_http_method_t *http_method_local_var = NULL;
    http_method_local_var = OpenAPI_http_method_create (
        );

    return http_method_local_var;
end:
    return NULL;
}

OpenAPI_http_method_t *OpenAPI_http_method_copy(OpenAPI_http_method_t *dst, OpenAPI_http_method_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_http_method_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_http_method_convertToJSON() failed");
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

    OpenAPI_http_method_free(dst);
    dst = OpenAPI_http_method_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

