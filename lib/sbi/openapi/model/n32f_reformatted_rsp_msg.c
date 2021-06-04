
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "n32f_reformatted_rsp_msg.h"

OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_create(
    OpenAPI_flat_jwe_json_t *reformatted_data,
    OpenAPI_list_t *modifications_block
    )
{
    OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg_local_var = OpenAPI_malloc(sizeof(OpenAPI_n32f_reformatted_rsp_msg_t));
    if (!n32f_reformatted_rsp_msg_local_var) {
        return NULL;
    }
    n32f_reformatted_rsp_msg_local_var->reformatted_data = reformatted_data;
    n32f_reformatted_rsp_msg_local_var->modifications_block = modifications_block;

    return n32f_reformatted_rsp_msg_local_var;
}

void OpenAPI_n32f_reformatted_rsp_msg_free(OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg)
{
    if (NULL == n32f_reformatted_rsp_msg) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_flat_jwe_json_free(n32f_reformatted_rsp_msg->reformatted_data);
    OpenAPI_list_for_each(n32f_reformatted_rsp_msg->modifications_block, node) {
        OpenAPI_flat_jws_json_free(node->data);
    }
    OpenAPI_list_free(n32f_reformatted_rsp_msg->modifications_block);
    ogs_free(n32f_reformatted_rsp_msg);
}

cJSON *OpenAPI_n32f_reformatted_rsp_msg_convertToJSON(OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg)
{
    cJSON *item = NULL;

    if (n32f_reformatted_rsp_msg == NULL) {
        ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed [N32fReformattedRspMsg]");
        return NULL;
    }

    item = cJSON_CreateObject();
    cJSON *reformatted_data_local_JSON = OpenAPI_flat_jwe_json_convertToJSON(n32f_reformatted_rsp_msg->reformatted_data);
    if (reformatted_data_local_JSON == NULL) {
        ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed [reformatted_data]");
        goto end;
    }
    cJSON_AddItemToObject(item, "reformattedData", reformatted_data_local_JSON);
    if (item->child == NULL) {
        ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed [reformatted_data]");
        goto end;
    }

    if (n32f_reformatted_rsp_msg->modifications_block) {
        cJSON *modifications_blockList = cJSON_AddArrayToObject(item, "modificationsBlock");
        if (modifications_blockList == NULL) {
            ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed [modifications_block]");
            goto end;
        }

        OpenAPI_lnode_t *modifications_block_node;
        if (n32f_reformatted_rsp_msg->modifications_block) {
            OpenAPI_list_for_each(n32f_reformatted_rsp_msg->modifications_block, modifications_block_node) {
                cJSON *itemLocal = OpenAPI_flat_jws_json_convertToJSON(modifications_block_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed [modifications_block]");
                    goto end;
                }
                cJSON_AddItemToArray(modifications_blockList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON(cJSON *n32f_reformatted_rsp_msgJSON)
{
    OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg_local_var = NULL;
    cJSON *reformatted_data = cJSON_GetObjectItemCaseSensitive(n32f_reformatted_rsp_msgJSON, "reformattedData");
    if (!reformatted_data) {
        ogs_error("OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON() failed [reformatted_data]");
        goto end;
    }

    OpenAPI_flat_jwe_json_t *reformatted_data_local_nonprim = NULL;

    reformatted_data_local_nonprim = OpenAPI_flat_jwe_json_parseFromJSON(reformatted_data);

    cJSON *modifications_block = cJSON_GetObjectItemCaseSensitive(n32f_reformatted_rsp_msgJSON, "modificationsBlock");

    OpenAPI_list_t *modifications_blockList;
    if (modifications_block) {
        cJSON *modifications_block_local_nonprimitive;
        if (!cJSON_IsArray(modifications_block)) {
            ogs_error("OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON() failed [modifications_block]");
            goto end;
        }

        modifications_blockList = OpenAPI_list_create();

        cJSON_ArrayForEach(modifications_block_local_nonprimitive, modifications_block ) {
            if (!cJSON_IsObject(modifications_block_local_nonprimitive)) {
                ogs_error("OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON() failed [modifications_block]");
                goto end;
            }
            OpenAPI_flat_jws_json_t *modifications_blockItem = OpenAPI_flat_jws_json_parseFromJSON(modifications_block_local_nonprimitive);

            OpenAPI_list_add(modifications_blockList, modifications_blockItem);
        }
    }

    n32f_reformatted_rsp_msg_local_var = OpenAPI_n32f_reformatted_rsp_msg_create (
        reformatted_data_local_nonprim,
        modifications_block ? modifications_blockList : NULL
        );

    return n32f_reformatted_rsp_msg_local_var;
end:
    return NULL;
}

OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_copy(OpenAPI_n32f_reformatted_rsp_msg_t *dst, OpenAPI_n32f_reformatted_rsp_msg_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_n32f_reformatted_rsp_msg_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_n32f_reformatted_rsp_msg_convertToJSON() failed");
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

    OpenAPI_n32f_reformatted_rsp_msg_free(dst);
    dst = OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

