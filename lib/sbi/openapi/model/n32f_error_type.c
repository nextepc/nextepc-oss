
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n32f_error_type.h"

OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_create(
    )
{
    OpenAPI_n32f_error_type_t *n32f_error_type_local_var = OpenAPI_malloc(sizeof(OpenAPI_n32f_error_type_t));
    if (!n32f_error_type_local_var) {
        return NULL;
    }

    return n32f_error_type_local_var;
}

void OpenAPI_n32f_error_type_free(OpenAPI_n32f_error_type_t *n32f_error_type)
{
    if (NULL == n32f_error_type) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(n32f_error_type);
}

cJSON *OpenAPI_n32f_error_type_convertToJSON(OpenAPI_n32f_error_type_t *n32f_error_type)
{
    cJSON *item = NULL;

    if (n32f_error_type == NULL) {
        ogs_error("OpenAPI_n32f_error_type_convertToJSON() failed [N32fErrorType]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_parseFromJSON(cJSON *n32f_error_typeJSON)
{
    OpenAPI_n32f_error_type_t *n32f_error_type_local_var = NULL;
    n32f_error_type_local_var = OpenAPI_n32f_error_type_create (
        );

    return n32f_error_type_local_var;
end:
    return NULL;
}

OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_copy(OpenAPI_n32f_error_type_t *dst, OpenAPI_n32f_error_type_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_n32f_error_type_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_n32f_error_type_convertToJSON() failed");
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

    OpenAPI_n32f_error_type_free(dst);
    dst = OpenAPI_n32f_error_type_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

