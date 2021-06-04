
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ie_info.h"

OpenAPI_ie_info_t *OpenAPI_ie_info_create(
    OpenAPI_ie_location_e ie_loc,
    OpenAPI_ie_type_e ie_type,
    char *req_ie,
    char *rsp_ie,
    int is_modifiable,
    OpenAPI_list_t* is_modifiable_by_ipx
    )
{
    OpenAPI_ie_info_t *ie_info_local_var = OpenAPI_malloc(sizeof(OpenAPI_ie_info_t));
    if (!ie_info_local_var) {
        return NULL;
    }
    ie_info_local_var->ie_loc = ie_loc;
    ie_info_local_var->ie_type = ie_type;
    ie_info_local_var->req_ie = req_ie;
    ie_info_local_var->rsp_ie = rsp_ie;
    ie_info_local_var->is_modifiable = is_modifiable;
    ie_info_local_var->is_modifiable_by_ipx = is_modifiable_by_ipx;

    return ie_info_local_var;
}

void OpenAPI_ie_info_free(OpenAPI_ie_info_t *ie_info)
{
    if (NULL == ie_info) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(ie_info->req_ie);
    ogs_free(ie_info->rsp_ie);
    OpenAPI_list_for_each(ie_info->is_modifiable_by_ipx, node) {
        OpenAPI_map_t *localKeyValue = (OpenAPI_map_t*)node->data;
        ogs_free(localKeyValue->value);
        ogs_free(localKeyValue);
    }
    OpenAPI_list_free(ie_info->is_modifiable_by_ipx);
    ogs_free(ie_info);
}

cJSON *OpenAPI_ie_info_convertToJSON(OpenAPI_ie_info_t *ie_info)
{
    cJSON *item = NULL;

    if (ie_info == NULL) {
        ogs_error("OpenAPI_ie_info_convertToJSON() failed [IeInfo]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "ieLoc", OpenAPI_ie_location_ToString(ie_info->ie_loc)) == NULL) {
        ogs_error("OpenAPI_ie_info_convertToJSON() failed [ie_loc]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "ieType", OpenAPI_ie_type_ToString(ie_info->ie_type)) == NULL) {
        ogs_error("OpenAPI_ie_info_convertToJSON() failed [ie_type]");
        goto end;
    }

    if (ie_info->req_ie) {
        if (cJSON_AddStringToObject(item, "reqIe", ie_info->req_ie) == NULL) {
            ogs_error("OpenAPI_ie_info_convertToJSON() failed [req_ie]");
            goto end;
        }
    }

    if (ie_info->rsp_ie) {
        if (cJSON_AddStringToObject(item, "rspIe", ie_info->rsp_ie) == NULL) {
            ogs_error("OpenAPI_ie_info_convertToJSON() failed [rsp_ie]");
            goto end;
        }
    }

    if (ie_info->is_modifiable) {
        if (cJSON_AddBoolToObject(item, "isModifiable", ie_info->is_modifiable) == NULL) {
            ogs_error("OpenAPI_ie_info_convertToJSON() failed [is_modifiable]");
            goto end;
        }
    }

    if (ie_info->is_modifiable_by_ipx) {
        cJSON *is_modifiable_by_ipx = cJSON_AddObjectToObject(item, "isModifiableByIpx");
        if (is_modifiable_by_ipx == NULL) {
            ogs_error("OpenAPI_ie_info_convertToJSON() failed [is_modifiable_by_ipx]");
            goto end;
        }
        cJSON *localMapObject = is_modifiable_by_ipx;
        OpenAPI_lnode_t *is_modifiable_by_ipx_node;
        if (ie_info->is_modifiable_by_ipx) {
            OpenAPI_list_for_each(ie_info->is_modifiable_by_ipx, is_modifiable_by_ipx_node) {
                OpenAPI_map_t *localKeyValue = (OpenAPI_map_t*)is_modifiable_by_ipx_node->data;
            }
        }
    }

end:
    return item;
}

OpenAPI_ie_info_t *OpenAPI_ie_info_parseFromJSON(cJSON *ie_infoJSON)
{
    OpenAPI_ie_info_t *ie_info_local_var = NULL;
    cJSON *ie_loc = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "ieLoc");
    if (!ie_loc) {
        ogs_error("OpenAPI_ie_info_parseFromJSON() failed [ie_loc]");
        goto end;
    }

    OpenAPI_ie_location_e ie_locVariable;

    if (!cJSON_IsString(ie_loc)) {
        ogs_error("OpenAPI_ie_info_parseFromJSON() failed [ie_loc]");
        goto end;
    }
    ie_locVariable = OpenAPI_ie_location_FromString(ie_loc->valuestring);

    cJSON *ie_type = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "ieType");
    if (!ie_type) {
        ogs_error("OpenAPI_ie_info_parseFromJSON() failed [ie_type]");
        goto end;
    }

    OpenAPI_ie_type_e ie_typeVariable;

    if (!cJSON_IsString(ie_type)) {
        ogs_error("OpenAPI_ie_info_parseFromJSON() failed [ie_type]");
        goto end;
    }
    ie_typeVariable = OpenAPI_ie_type_FromString(ie_type->valuestring);

    cJSON *req_ie = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "reqIe");

    if (req_ie) {
        if (!cJSON_IsString(req_ie)) {
            ogs_error("OpenAPI_ie_info_parseFromJSON() failed [req_ie]");
            goto end;
        }
    }

    cJSON *rsp_ie = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "rspIe");

    if (rsp_ie) {
        if (!cJSON_IsString(rsp_ie)) {
            ogs_error("OpenAPI_ie_info_parseFromJSON() failed [rsp_ie]");
            goto end;
        }
    }

    cJSON *is_modifiable = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "isModifiable");

    if (is_modifiable) {
        if (!cJSON_IsBool(is_modifiable)) {
            ogs_error("OpenAPI_ie_info_parseFromJSON() failed [is_modifiable]");
            goto end;
        }
    }

    cJSON *is_modifiable_by_ipx = cJSON_GetObjectItemCaseSensitive(ie_infoJSON, "isModifiableByIpx");

    OpenAPI_list_t *is_modifiable_by_ipxList;
    if (is_modifiable_by_ipx) {
        cJSON *is_modifiable_by_ipx_local_map;
        if (!cJSON_IsObject(is_modifiable_by_ipx)) {
            ogs_error("OpenAPI_ie_info_parseFromJSON() failed [is_modifiable_by_ipx]");
            goto end;
        }
        is_modifiable_by_ipxList = OpenAPI_list_create();
        OpenAPI_map_t *localMapKeyPair = NULL;
        cJSON_ArrayForEach(is_modifiable_by_ipx_local_map, is_modifiable_by_ipx) {
            cJSON *localMapObject = is_modifiable_by_ipx_local_map;
            OpenAPI_list_add(is_modifiable_by_ipxList, localMapKeyPair);
        }
    }

    ie_info_local_var = OpenAPI_ie_info_create (
        ie_locVariable,
        ie_typeVariable,
        req_ie ? ogs_strdup(req_ie->valuestring) : NULL,
        rsp_ie ? ogs_strdup(rsp_ie->valuestring) : NULL,
        is_modifiable ? is_modifiable->valueint : 0,
        is_modifiable_by_ipx ? is_modifiable_by_ipxList : NULL
        );

    return ie_info_local_var;
end:
    return NULL;
}

OpenAPI_ie_info_t *OpenAPI_ie_info_copy(OpenAPI_ie_info_t *dst, OpenAPI_ie_info_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_ie_info_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_ie_info_convertToJSON() failed");
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

    OpenAPI_ie_info_free(dst);
    dst = OpenAPI_ie_info_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

