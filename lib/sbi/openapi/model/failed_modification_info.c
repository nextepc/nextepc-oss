
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "failed_modification_info.h"

OpenAPI_failed_modification_info_t *OpenAPI_failed_modification_info_create(
    char *ipx_id,
    OpenAPI_n32f_error_type_t *n32f_error_type
    )
{
    OpenAPI_failed_modification_info_t *failed_modification_info_local_var = OpenAPI_malloc(sizeof(OpenAPI_failed_modification_info_t));
    if (!failed_modification_info_local_var) {
        return NULL;
    }
    failed_modification_info_local_var->ipx_id = ipx_id;
    failed_modification_info_local_var->n32f_error_type = n32f_error_type;

    return failed_modification_info_local_var;
}

void OpenAPI_failed_modification_info_free(OpenAPI_failed_modification_info_t *failed_modification_info)
{
    if (NULL == failed_modification_info) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(failed_modification_info->ipx_id);
    OpenAPI_n32f_error_type_free(failed_modification_info->n32f_error_type);
    ogs_free(failed_modification_info);
}

cJSON *OpenAPI_failed_modification_info_convertToJSON(OpenAPI_failed_modification_info_t *failed_modification_info)
{
    cJSON *item = NULL;

    if (failed_modification_info == NULL) {
        ogs_error("OpenAPI_failed_modification_info_convertToJSON() failed [FailedModificationInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "ipxId", failed_modification_info->ipx_id) == NULL) {
        ogs_error("OpenAPI_failed_modification_info_convertToJSON() failed [ipx_id]");
        goto end;
    }

    cJSON *n32f_error_type_local_JSON = OpenAPI_n32f_error_type_convertToJSON(failed_modification_info->n32f_error_type);
    if (n32f_error_type_local_JSON == NULL) {
        ogs_error("OpenAPI_failed_modification_info_convertToJSON() failed [n32f_error_type]");
        goto end;
    }
    cJSON_AddItemToObject(item, "n32fErrorType", n32f_error_type_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_failed_modification_info_convertToJSON() failed [n32f_error_type]");
        goto end;
    }

end:
    return item;
}

OpenAPI_failed_modification_info_t *OpenAPI_failed_modification_info_parseFromJSON(cJSON *failed_modification_infoJSON)
{
    OpenAPI_failed_modification_info_t *failed_modification_info_local_var = NULL;
    cJSON *ipx_id = cJSON_GetObjectItemCaseSensitive(failed_modification_infoJSON, "ipxId");
    if (!ipx_id) {
        ogs_error("OpenAPI_failed_modification_info_parseFromJSON() failed [ipx_id]");
        goto end;
    }


    if (!cJSON_IsString(ipx_id)) {
        ogs_error("OpenAPI_failed_modification_info_parseFromJSON() failed [ipx_id]");
        goto end;
    }

    cJSON *n32f_error_type = cJSON_GetObjectItemCaseSensitive(failed_modification_infoJSON, "n32fErrorType");
    if (!n32f_error_type) {
        ogs_error("OpenAPI_failed_modification_info_parseFromJSON() failed [n32f_error_type]");
        goto end;
    }

    OpenAPI_n32f_error_type_t *n32f_error_type_local_nonprim = NULL;

    n32f_error_type_local_nonprim = OpenAPI_n32f_error_type_parseFromJSON(n32f_error_type);

    failed_modification_info_local_var = OpenAPI_failed_modification_info_create (
        ogs_strdup(ipx_id->valuestring),
        n32f_error_type_local_nonprim
        );

    return failed_modification_info_local_var;
end:
    return NULL;
}

OpenAPI_failed_modification_info_t *OpenAPI_failed_modification_info_copy(OpenAPI_failed_modification_info_t *dst, OpenAPI_failed_modification_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_failed_modification_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_failed_modification_info_convertToJSON() failed");
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

    OpenAPI_failed_modification_info_free(dst);
    dst = OpenAPI_failed_modification_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

