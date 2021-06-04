
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "index_to_encrypted_value.h"

OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_create(
    int enc_block_index
    )
{
    OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value_local_var = OpenAPI_malloc(sizeof(OpenAPI_index_to_encrypted_value_t));
    if (!index_to_encrypted_value_local_var) {
        return NULL;
    }
    index_to_encrypted_value_local_var->enc_block_index = enc_block_index;

    return index_to_encrypted_value_local_var;
}

void OpenAPI_index_to_encrypted_value_free(OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value)
{
    if (NULL == index_to_encrypted_value) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(index_to_encrypted_value);
}

cJSON *OpenAPI_index_to_encrypted_value_convertToJSON(OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value)
{
    cJSON *item = NULL;

    if (index_to_encrypted_value == NULL) {
        ogs_error("OpenAPI_index_to_encrypted_value_convertToJSON() failed [IndexToEncryptedValue]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddNumberToObject(item, "encBlockIndex", index_to_encrypted_value->enc_block_index) == NULL) {
        ogs_error("OpenAPI_index_to_encrypted_value_convertToJSON() failed [enc_block_index]");
        goto end;
    }

end:
    return item;
}

OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_parseFromJSON(cJSON *index_to_encrypted_valueJSON)
{
    OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value_local_var = NULL;
    cJSON *enc_block_index = cJSON_GetObjectItemCaseSensitive(index_to_encrypted_valueJSON, "encBlockIndex");
    if (!enc_block_index) {
        ogs_error("OpenAPI_index_to_encrypted_value_parseFromJSON() failed [enc_block_index]");
        goto end;
    }


    if (!cJSON_IsNumber(enc_block_index)) {
        ogs_error("OpenAPI_index_to_encrypted_value_parseFromJSON() failed [enc_block_index]");
        goto end;
    }

    index_to_encrypted_value_local_var = OpenAPI_index_to_encrypted_value_create (
        enc_block_index->valuedouble
        );

    return index_to_encrypted_value_local_var;
end:
    return NULL;
}

OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_copy(OpenAPI_index_to_encrypted_value_t *dst, OpenAPI_index_to_encrypted_value_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_index_to_encrypted_value_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_index_to_encrypted_value_convertToJSON() failed");
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

    OpenAPI_index_to_encrypted_value_free(dst);
    dst = OpenAPI_index_to_encrypted_value_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

