
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "meta_data.h"

OpenAPI_meta_data_t *OpenAPI_meta_data_create(
    char *n32f_context_id,
    char *message_id,
    char *authorized_ipx_id
    )
{
    OpenAPI_meta_data_t *meta_data_local_var = OpenAPI_malloc(sizeof(OpenAPI_meta_data_t));
    if (!meta_data_local_var) {
        return NULL;
    }
    meta_data_local_var->n32f_context_id = n32f_context_id;
    meta_data_local_var->message_id = message_id;
    meta_data_local_var->authorized_ipx_id = authorized_ipx_id;

    return meta_data_local_var;
}

void OpenAPI_meta_data_free(OpenAPI_meta_data_t *meta_data)
{
    if (NULL == meta_data) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(meta_data->n32f_context_id);
    ogs_free(meta_data->message_id);
    ogs_free(meta_data->authorized_ipx_id);
    ogs_free(meta_data);
}

cJSON *OpenAPI_meta_data_convertToJSON(OpenAPI_meta_data_t *meta_data)
{
    cJSON *item = NULL;

    if (meta_data == NULL) {
        ogs_error("OpenAPI_meta_data_convertToJSON() failed [MetaData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "n32fContextId", meta_data->n32f_context_id) == NULL) {
        ogs_error("OpenAPI_meta_data_convertToJSON() failed [n32f_context_id]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "messageId", meta_data->message_id) == NULL) {
        ogs_error("OpenAPI_meta_data_convertToJSON() failed [message_id]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "authorizedIpxId", meta_data->authorized_ipx_id) == NULL) {
        ogs_error("OpenAPI_meta_data_convertToJSON() failed [authorized_ipx_id]");
        goto end;
    }

end:
    return item;
}

OpenAPI_meta_data_t *OpenAPI_meta_data_parseFromJSON(cJSON *meta_dataJSON)
{
    OpenAPI_meta_data_t *meta_data_local_var = NULL;
    cJSON *n32f_context_id = cJSON_GetObjectItemCaseSensitive(meta_dataJSON, "n32fContextId");
    if (!n32f_context_id) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [n32f_context_id]");
        goto end;
    }


    if (!cJSON_IsString(n32f_context_id)) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [n32f_context_id]");
        goto end;
    }

    cJSON *message_id = cJSON_GetObjectItemCaseSensitive(meta_dataJSON, "messageId");
    if (!message_id) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [message_id]");
        goto end;
    }


    if (!cJSON_IsString(message_id)) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [message_id]");
        goto end;
    }

    cJSON *authorized_ipx_id = cJSON_GetObjectItemCaseSensitive(meta_dataJSON, "authorizedIpxId");
    if (!authorized_ipx_id) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [authorized_ipx_id]");
        goto end;
    }


    if (!cJSON_IsString(authorized_ipx_id)) {
        ogs_error("OpenAPI_meta_data_parseFromJSON() failed [authorized_ipx_id]");
        goto end;
    }

    meta_data_local_var = OpenAPI_meta_data_create (
        ogs_strdup(n32f_context_id->valuestring),
        ogs_strdup(message_id->valuestring),
        ogs_strdup(authorized_ipx_id->valuestring)
        );

    return meta_data_local_var;
end:
    return NULL;
}

OpenAPI_meta_data_t *OpenAPI_meta_data_copy(OpenAPI_meta_data_t *dst, OpenAPI_meta_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_meta_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_meta_data_convertToJSON() failed");
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

    OpenAPI_meta_data_free(dst);
    dst = OpenAPI_meta_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

