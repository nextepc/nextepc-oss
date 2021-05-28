
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sec_negotiate_rsp_data.h"

OpenAPI_sec_negotiate_rsp_data_t *OpenAPI_sec_negotiate_rsp_data_create(
    char *sender,
    OpenAPI_security_capability_t *selected_sec_capability,
    int _3_gpp_sbi_target_api_root_supported,
    OpenAPI_list_t *plmn_id_list
    )
{
    OpenAPI_sec_negotiate_rsp_data_t *sec_negotiate_rsp_data_local_var = OpenAPI_malloc(sizeof(OpenAPI_sec_negotiate_rsp_data_t));
    if (!sec_negotiate_rsp_data_local_var) {
        return NULL;
    }
    sec_negotiate_rsp_data_local_var->sender = sender;
    sec_negotiate_rsp_data_local_var->selected_sec_capability = selected_sec_capability;
    sec_negotiate_rsp_data_local_var->_3_gpp_sbi_target_api_root_supported = _3_gpp_sbi_target_api_root_supported;
    sec_negotiate_rsp_data_local_var->plmn_id_list = plmn_id_list;

    return sec_negotiate_rsp_data_local_var;
}

void OpenAPI_sec_negotiate_rsp_data_free(OpenAPI_sec_negotiate_rsp_data_t *sec_negotiate_rsp_data)
{
    if (NULL == sec_negotiate_rsp_data) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(sec_negotiate_rsp_data->sender);
    OpenAPI_security_capability_free(sec_negotiate_rsp_data->selected_sec_capability);
    OpenAPI_list_for_each(sec_negotiate_rsp_data->plmn_id_list, node) {
        OpenAPI_plmn_id_free(node->data);
    }
    OpenAPI_list_free(sec_negotiate_rsp_data->plmn_id_list);
    ogs_free(sec_negotiate_rsp_data);
}

cJSON *OpenAPI_sec_negotiate_rsp_data_convertToJSON(OpenAPI_sec_negotiate_rsp_data_t *sec_negotiate_rsp_data)
{
    cJSON *item = NULL;

    if (sec_negotiate_rsp_data == NULL) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [SecNegotiateRspData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "sender", sec_negotiate_rsp_data->sender) == NULL) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [sender]");
        goto end;
    }

    cJSON *selected_sec_capability_local_JSON = OpenAPI_security_capability_convertToJSON(sec_negotiate_rsp_data->selected_sec_capability);
    if (selected_sec_capability_local_JSON == NULL) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [selected_sec_capability]");
        goto end;
    }
    cJSON_AddItemToObject(item, "selectedSecCapability", selected_sec_capability_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [selected_sec_capability]");
        goto end;
    }

    if (sec_negotiate_rsp_data->_3_gpp_sbi_target_api_root_supported) {
        if (cJSON_AddBoolToObject(item, "3GppSbiTargetApiRootSupported", sec_negotiate_rsp_data->_3_gpp_sbi_target_api_root_supported) == NULL) {
            ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [_3_gpp_sbi_target_api_root_supported]");
            goto end;
        }
    }

    if (sec_negotiate_rsp_data->plmn_id_list) {
        cJSON *plmn_id_listList = cJSON_AddArrayToObject(item, "plmnIdList");
        if (plmn_id_listList == NULL) {
            ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [plmn_id_list]");
            goto end;
        }

        OpenAPI_lnode_t *plmn_id_list_node;
        if (sec_negotiate_rsp_data->plmn_id_list) {
            OpenAPI_list_for_each(sec_negotiate_rsp_data->plmn_id_list, plmn_id_list_node) {
                cJSON *itemLocal = OpenAPI_plmn_id_convertToJSON(plmn_id_list_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed [plmn_id_list]");
                    goto end;
                }
                cJSON_AddItemToArray(plmn_id_listList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_sec_negotiate_rsp_data_t *OpenAPI_sec_negotiate_rsp_data_parseFromJSON(cJSON *sec_negotiate_rsp_dataJSON)
{
    OpenAPI_sec_negotiate_rsp_data_t *sec_negotiate_rsp_data_local_var = NULL;
    cJSON *sender = cJSON_GetObjectItemCaseSensitive(sec_negotiate_rsp_dataJSON, "sender");
    if (!sender) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [sender]");
        goto end;
    }


    if (!cJSON_IsString(sender)) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [sender]");
        goto end;
    }

    cJSON *selected_sec_capability = cJSON_GetObjectItemCaseSensitive(sec_negotiate_rsp_dataJSON, "selectedSecCapability");
    if (!selected_sec_capability) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [selected_sec_capability]");
        goto end;
    }

    OpenAPI_security_capability_t *selected_sec_capability_local_nonprim = NULL;

    selected_sec_capability_local_nonprim = OpenAPI_security_capability_parseFromJSON(selected_sec_capability);

    cJSON *_3_gpp_sbi_target_api_root_supported = cJSON_GetObjectItemCaseSensitive(sec_negotiate_rsp_dataJSON, "3GppSbiTargetApiRootSupported");

    if (_3_gpp_sbi_target_api_root_supported) {
        if (!cJSON_IsBool(_3_gpp_sbi_target_api_root_supported)) {
            ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [_3_gpp_sbi_target_api_root_supported]");
            goto end;
        }
    }

    cJSON *plmn_id_list = cJSON_GetObjectItemCaseSensitive(sec_negotiate_rsp_dataJSON, "plmnIdList");

    OpenAPI_list_t *plmn_id_listList;
    if (plmn_id_list) {
        cJSON *plmn_id_list_local_nonprimitive;
        if (!cJSON_IsArray(plmn_id_list)) {
            ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [plmn_id_list]");
            goto end;
        }

        plmn_id_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(plmn_id_list_local_nonprimitive, plmn_id_list ) {
            if (!cJSON_IsObject(plmn_id_list_local_nonprimitive)) {
                ogs_error("OpenAPI_sec_negotiate_rsp_data_parseFromJSON() failed [plmn_id_list]");
                goto end;
            }
            OpenAPI_plmn_id_t *plmn_id_listItem = OpenAPI_plmn_id_parseFromJSON(plmn_id_list_local_nonprimitive);

            OpenAPI_list_add(plmn_id_listList, plmn_id_listItem);
        }
    }

    sec_negotiate_rsp_data_local_var = OpenAPI_sec_negotiate_rsp_data_create (
        ogs_strdup(sender->valuestring),
        selected_sec_capability_local_nonprim,
        _3_gpp_sbi_target_api_root_supported ? _3_gpp_sbi_target_api_root_supported->valueint : 0,
        plmn_id_list ? plmn_id_listList : NULL
        );

    return sec_negotiate_rsp_data_local_var;
end:
    return NULL;
}

OpenAPI_sec_negotiate_rsp_data_t *OpenAPI_sec_negotiate_rsp_data_copy(OpenAPI_sec_negotiate_rsp_data_t *dst, OpenAPI_sec_negotiate_rsp_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_sec_negotiate_rsp_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_sec_negotiate_rsp_data_convertToJSON() failed");
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

    OpenAPI_sec_negotiate_rsp_data_free(dst);
    dst = OpenAPI_sec_negotiate_rsp_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

