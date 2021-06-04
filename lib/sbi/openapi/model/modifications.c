
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "modifications.h"

OpenAPI_modifications_t *OpenAPI_modifications_create(
    char *identity,
    OpenAPI_list_t *operations
    )
{
    OpenAPI_modifications_t *modifications_local_var = OpenAPI_malloc(sizeof(OpenAPI_modifications_t));
    if (!modifications_local_var) {
        return NULL;
    }
    modifications_local_var->identity = identity;
    modifications_local_var->operations = operations;

    return modifications_local_var;
}

void OpenAPI_modifications_free(OpenAPI_modifications_t *modifications)
{
    if (NULL == modifications) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(modifications->identity);
    OpenAPI_list_for_each(modifications->operations, node) {
        OpenAPI_patch_item_free(node->data);
    }
    OpenAPI_list_free(modifications->operations);
    ogs_free(modifications);
}

cJSON *OpenAPI_modifications_convertToJSON(OpenAPI_modifications_t *modifications)
{
    cJSON *item = NULL;

    if (modifications == NULL) {
        ogs_error("OpenAPI_modifications_convertToJSON() failed [Modifications]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "identity", modifications->identity) == NULL) {
        ogs_error("OpenAPI_modifications_convertToJSON() failed [identity]");
        goto end;
    }

    if (modifications->operations) {
        cJSON *operationsList = cJSON_AddArrayToObject(item, "operations");
        if (operationsList == NULL) {
            ogs_error("OpenAPI_modifications_convertToJSON() failed [operations]");
            goto end;
        }

        OpenAPI_lnode_t *operations_node;
        if (modifications->operations) {
            OpenAPI_list_for_each(modifications->operations, operations_node) {
                cJSON *itemLocal = OpenAPI_patch_item_convertToJSON(operations_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_modifications_convertToJSON() failed [operations]");
                    goto end;
                }
                cJSON_AddItemToArray(operationsList, itemLocal);
            }
        }
    }

end:
    return item;
}

OpenAPI_modifications_t *OpenAPI_modifications_parseFromJSON(cJSON *modificationsJSON)
{
    OpenAPI_modifications_t *modifications_local_var = NULL;
    cJSON *identity = cJSON_GetObjectItemCaseSensitive(modificationsJSON, "identity");
    if (!identity) {
        ogs_error("OpenAPI_modifications_parseFromJSON() failed [identity]");
        goto end;
    }


    if (!cJSON_IsString(identity)) {
        ogs_error("OpenAPI_modifications_parseFromJSON() failed [identity]");
        goto end;
    }

    cJSON *operations = cJSON_GetObjectItemCaseSensitive(modificationsJSON, "operations");

    OpenAPI_list_t *operationsList;
    if (operations) {
        cJSON *operations_local_nonprimitive;
        if (!cJSON_IsArray(operations)) {
            ogs_error("OpenAPI_modifications_parseFromJSON() failed [operations]");
            goto end;
        }

        operationsList = OpenAPI_list_create();

        cJSON_ArrayForEach(operations_local_nonprimitive, operations ) {
            if (!cJSON_IsObject(operations_local_nonprimitive)) {
                ogs_error("OpenAPI_modifications_parseFromJSON() failed [operations]");
                goto end;
            }
            OpenAPI_patch_item_t *operationsItem = OpenAPI_patch_item_parseFromJSON(operations_local_nonprimitive);

            OpenAPI_list_add(operationsList, operationsItem);
        }
    }

    modifications_local_var = OpenAPI_modifications_create (
        ogs_strdup(identity->valuestring),
        operations ? operationsList : NULL
        );

    return modifications_local_var;
end:
    return NULL;
}

OpenAPI_modifications_t *OpenAPI_modifications_copy(OpenAPI_modifications_t *dst, OpenAPI_modifications_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_modifications_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_modifications_convertToJSON() failed");
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

    OpenAPI_modifications_free(dst);
    dst = OpenAPI_modifications_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

