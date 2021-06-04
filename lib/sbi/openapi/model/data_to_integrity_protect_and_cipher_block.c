
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_to_integrity_protect_and_cipher_block.h"

OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_create(
    OpenAPI_list_t *data_to_encrypt
    )
{
    OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block_local_var = OpenAPI_malloc(sizeof(OpenAPI_data_to_integrity_protect_and_cipher_block_t));
    if (!data_to_integrity_protect_and_cipher_block_local_var) {
        return NULL;
    }
    data_to_integrity_protect_and_cipher_block_local_var->data_to_encrypt = data_to_encrypt;

    return data_to_integrity_protect_and_cipher_block_local_var;
}

void OpenAPI_data_to_integrity_protect_and_cipher_block_free(OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block)
{
    if (NULL == data_to_integrity_protect_and_cipher_block) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_list_for_each(data_to_integrity_protect_and_cipher_block->data_to_encrypt, node) {
        OpenAPI_any_type_free(node->data);
    }
    OpenAPI_list_free(data_to_integrity_protect_and_cipher_block->data_to_encrypt);
    ogs_free(data_to_integrity_protect_and_cipher_block);
}

cJSON *OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON(OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block)
{
    cJSON *item = NULL;

    if (data_to_integrity_protect_and_cipher_block == NULL) {
        ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON() failed [DataToIntegrityProtectAndCipherBlock]");
        return NULL;
    }

    item = cJSON_CreateObject();
    cJSON *data_to_encryptList = cJSON_AddArrayToObject(item, "dataToEncrypt");
    if (data_to_encryptList == NULL) {
        ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON() failed [data_to_encrypt]");
        goto end;
    }

    OpenAPI_lnode_t *data_to_encrypt_node;
    if (data_to_integrity_protect_and_cipher_block->data_to_encrypt) {
        OpenAPI_list_for_each(data_to_integrity_protect_and_cipher_block->data_to_encrypt, data_to_encrypt_node) {
            cJSON *itemLocal = OpenAPI_any_type_convertToJSON(data_to_encrypt_node->data);
            if (itemLocal == NULL) {
                ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON() failed [data_to_encrypt]");
                goto end;
            }
            cJSON_AddItemToArray(data_to_encryptList, itemLocal);
        }
    }

end:
    return item;
}

OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON(cJSON *data_to_integrity_protect_and_cipher_blockJSON)
{
    OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block_local_var = NULL;
    cJSON *data_to_encrypt = cJSON_GetObjectItemCaseSensitive(data_to_integrity_protect_and_cipher_blockJSON, "dataToEncrypt");
    if (!data_to_encrypt) {
        ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON() failed [data_to_encrypt]");
        goto end;
    }

    OpenAPI_list_t *data_to_encryptList;

    cJSON *data_to_encrypt_local_nonprimitive;
    if (!cJSON_IsArray(data_to_encrypt)) {
        ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON() failed [data_to_encrypt]");
        goto end;
    }

    data_to_encryptList = OpenAPI_list_create();

    cJSON_ArrayForEach(data_to_encrypt_local_nonprimitive, data_to_encrypt ) {
        if (!cJSON_IsObject(data_to_encrypt_local_nonprimitive)) {
            ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON() failed [data_to_encrypt]");
            goto end;
        }
        OpenAPI_any_type_t *data_to_encryptItem = OpenAPI_any_type_parseFromJSON(data_to_encrypt_local_nonprimitive);

        OpenAPI_list_add(data_to_encryptList, data_to_encryptItem);
    }

    data_to_integrity_protect_and_cipher_block_local_var = OpenAPI_data_to_integrity_protect_and_cipher_block_create (
        data_to_encryptList
        );

    return data_to_integrity_protect_and_cipher_block_local_var;
end:
    return NULL;
}

OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_copy(OpenAPI_data_to_integrity_protect_and_cipher_block_t *dst, OpenAPI_data_to_integrity_protect_and_cipher_block_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON() failed");
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

    OpenAPI_data_to_integrity_protect_and_cipher_block_free(dst);
    dst = OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

