
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sec_negotiate_req_data.h"

OpenAPI_sec_negotiate_req_data_t *OpenAPI_sec_negotiate_req_data_create(
    char *sender,
    OpenAPI_list_t *supported_sec_capability_list,
    int _3_gpp_sbi_target_api_root_supported,
    OpenAPI_list_t *plmn_id_list
    )
{
    OpenAPI_sec_negotiate_req_data_t *sec_negotiate_req_data_local_var = OpenAPI_malloc(sizeof(OpenAPI_sec_negotiate_req_data_t));
    if (!sec_negotiate_req_data_local_var) {
        return NULL;
    }
    sec_negotiate_req_data_local_var->sender = sender;
    sec_negotiate_req_data_local_var->supported_sec_capability_list = supported_sec_capability_list;
    sec_negotiate_req_data_local_var->_3_gpp_sbi_target_api_root_supported = _3_gpp_sbi_target_api_root_supported;
    sec_negotiate_req_data_local_var->plmn_id_list = plmn_id_list;

    return sec_negotiate_req_data_local_var;
}

void OpenAPI_sec_negotiate_req_data_free(OpenAPI_sec_negotiate_req_data_t *sec_negotiate_req_data)
{
    if (NULL == sec_negotiate_req_data) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(sec_negotiate_req_data->sender);
    OpenAPI_list_for_each(sec_negotiate_req_data->supported_sec_capability_list, node) {
        OpenAPI_security_capability_free(node->data);
    }
    OpenAPI_list_free(sec_negotiate_req_data->supported_sec_capability_list);
    OpenAPI_list_for_each(sec_negotiate_req_data->plmn_id_list, node) {
        OpenAPI_plmn_id_free(node->data);
    }
    OpenAPI_list_free(sec_negotiate_req_data->plmn_id_list);
    ogs_free(sec_negotiate_req_data);
}

cJSON *OpenAPI_sec_negotiate_req_data_convertToJSON(OpenAPI_sec_negotiate_req_data_t *sec_negotiate_req_data)
{
    cJSON *item = NULL;

    if (sec_negotiate_req_data == NULL) {
        ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [SecNegotiateReqData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "sender", sec_negotiate_req_data->sender) == NULL) {
        ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [sender]");
        goto end;
    }

    cJSON *supported_sec_capability_listList = cJSON_AddArrayToObject(item, "supportedSecCapabilityList");
    if (supported_sec_capability_listList == NULL) {
        ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [supported_sec_capability_list]");
        goto end;
    }

    OpenAPI_lnode_t *supported_sec_capability_list_node;
    if (sec_negotiate_req_data->supported_sec_capability_list) {
        OpenAPI_list_for_each(sec_negotiate_req_data->supported_sec_capability_list, supported_sec_capability_list_node) {
            cJSON *itemLocal = OpenAPI_security_capability_convertToJSON(supported_sec_capability_list_node->data);
            if (itemLocal == NULL) {
                ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [supported_sec_capability_list]");
                goto end;
            }
            cJSON_AddItemToArray(supported_sec_capability_listList, itemLocal);
        }
    }

    if (sec_negotiate_req_data->_3_gpp_sbi_target_api_root_supported) {
        if (cJSON_AddBoolToObject(item, "3GppSbiTargetApiRootSupported", sec_negotiate_req_data->_3_gpp_sbi_target_api_root_supported) == NULL) {
            ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [_3_gpp_sbi_target_api_root_supported]");
            goto end;
        }
    }

    if (sec_negotiate_req_data->plmn_id_list) {
        cJSON *plmn_id_listList = cJSON_AddArrayToObject(item, "plmnIdList");
        if (plmn_id_listList == NULL) {
            ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [plmn_id_list]");
            goto end;
        }

        OpenAPI_lnode_t *plmn_id_list_node;
        if (sec_negotiate_req_data->plmn_id_list) {
            OpenAPI_list_for_each(sec_negotiate_req_data->plmn_id_list, plmn_id_list_node) {
                cJSON *itemLocal = OpenAPI_plmn_id_convertToJSON(plmn_id_list_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed [plmn_id_list]");
                    goto end;
                }
                cJSON_AddItemToArray(plmn_id_listList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_sec_negotiate_req_data_t *OpenAPI_sec_negotiate_req_data_parseFromJSON(cJSON *sec_negotiate_req_dataJSON)
{
    OpenAPI_sec_negotiate_req_data_t *sec_negotiate_req_data_local_var = NULL;
    cJSON *sender = cJSON_GetObjectItemCaseSensitive(sec_negotiate_req_dataJSON, "sender");
    if (!sender) {
        ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [sender]");
        goto end;
    }


    if (!cJSON_IsString(sender)) {
        ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [sender]");
        goto end;
    }

    cJSON *supported_sec_capability_list = cJSON_GetObjectItemCaseSensitive(sec_negotiate_req_dataJSON, "supportedSecCapabilityList");
    if (!supported_sec_capability_list) {
        ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [supported_sec_capability_list]");
        goto end;
    }

    OpenAPI_list_t *supported_sec_capability_listList;

    cJSON *supported_sec_capability_list_local_nonprimitive;
    if (!cJSON_IsArray(supported_sec_capability_list)) {
        ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [supported_sec_capability_list]");
        goto end;
    }

    supported_sec_capability_listList = OpenAPI_list_create();

    cJSON_ArrayForEach(supported_sec_capability_list_local_nonprimitive, supported_sec_capability_list ) {
        if (!cJSON_IsObject(supported_sec_capability_list_local_nonprimitive)) {
            ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [supported_sec_capability_list]");
            goto end;
        }
        OpenAPI_security_capability_t *supported_sec_capability_listItem = OpenAPI_security_capability_parseFromJSON(supported_sec_capability_list_local_nonprimitive);

        OpenAPI_list_add(supported_sec_capability_listList, supported_sec_capability_listItem);
    }

    cJSON *_3_gpp_sbi_target_api_root_supported = cJSON_GetObjectItemCaseSensitive(sec_negotiate_req_dataJSON, "3GppSbiTargetApiRootSupported");

    if (_3_gpp_sbi_target_api_root_supported) {
        if (!cJSON_IsBool(_3_gpp_sbi_target_api_root_supported)) {
            ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [_3_gpp_sbi_target_api_root_supported]");
            goto end;
        }
    }

    cJSON *plmn_id_list = cJSON_GetObjectItemCaseSensitive(sec_negotiate_req_dataJSON, "plmnIdList");

    OpenAPI_list_t *plmn_id_listList;
    if (plmn_id_list) {
        cJSON *plmn_id_list_local_nonprimitive;
        if (!cJSON_IsArray(plmn_id_list)) {
            ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [plmn_id_list]");
            goto end;
        }

        plmn_id_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(plmn_id_list_local_nonprimitive, plmn_id_list ) {
            if (!cJSON_IsObject(plmn_id_list_local_nonprimitive)) {
                ogs_error("OpenAPI_sec_negotiate_req_data_parseFromJSON() failed [plmn_id_list]");
                goto end;
            }
            OpenAPI_plmn_id_t *plmn_id_listItem = OpenAPI_plmn_id_parseFromJSON(plmn_id_list_local_nonprimitive);

            OpenAPI_list_add(plmn_id_listList, plmn_id_listItem);
        }
    }

    sec_negotiate_req_data_local_var = OpenAPI_sec_negotiate_req_data_create (
        ogs_strdup(sender->valuestring),
        supported_sec_capability_listList,
        _3_gpp_sbi_target_api_root_supported ? _3_gpp_sbi_target_api_root_supported->valueint : 0,
        plmn_id_list ? plmn_id_listList : NULL
        );

    return sec_negotiate_req_data_local_var;
end:
    return NULL;
}

OpenAPI_sec_negotiate_req_data_t *OpenAPI_sec_negotiate_req_data_copy(OpenAPI_sec_negotiate_req_data_t *dst, OpenAPI_sec_negotiate_req_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_sec_negotiate_req_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_sec_negotiate_req_data_convertToJSON() failed");
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

    OpenAPI_sec_negotiate_req_data_free(dst);
    dst = OpenAPI_sec_negotiate_req_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

