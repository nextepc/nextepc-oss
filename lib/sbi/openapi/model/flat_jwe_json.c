
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "flat_jwe_json.h"

OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_create(
    char *protected,
    OpenAPI_object_t *unprotected,
    OpenAPI_object_t *header,
    char *encrypted_key,
    char *aad,
    char *iv,
    char *ciphertext,
    char *tag
    )
{
    OpenAPI_flat_jwe_json_t *flat_jwe_json_local_var = OpenAPI_malloc(sizeof(OpenAPI_flat_jwe_json_t));
    if (!flat_jwe_json_local_var) {
        return NULL;
    }
    flat_jwe_json_local_var->protected = protected;
    flat_jwe_json_local_var->unprotected = unprotected;
    flat_jwe_json_local_var->header = header;
    flat_jwe_json_local_var->encrypted_key = encrypted_key;
    flat_jwe_json_local_var->aad = aad;
    flat_jwe_json_local_var->iv = iv;
    flat_jwe_json_local_var->ciphertext = ciphertext;
    flat_jwe_json_local_var->tag = tag;

    return flat_jwe_json_local_var;
}

void OpenAPI_flat_jwe_json_free(OpenAPI_flat_jwe_json_t *flat_jwe_json)
{
    if (NULL == flat_jwe_json) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(flat_jwe_json->protected);
    OpenAPI_object_free(flat_jwe_json->unprotected);
    OpenAPI_object_free(flat_jwe_json->header);
    ogs_free(flat_jwe_json->encrypted_key);
    ogs_free(flat_jwe_json->aad);
    ogs_free(flat_jwe_json->iv);
    ogs_free(flat_jwe_json->ciphertext);
    ogs_free(flat_jwe_json->tag);
    ogs_free(flat_jwe_json);
}

cJSON *OpenAPI_flat_jwe_json_convertToJSON(OpenAPI_flat_jwe_json_t *flat_jwe_json)
{
    cJSON *item = NULL;

    if (flat_jwe_json == NULL) {
        ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [FlatJweJson]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (flat_jwe_json->protected) {
        if (cJSON_AddStringToObject(item, "protected", flat_jwe_json->protected) == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [protected]");
            goto end;
        }
    }

    if (flat_jwe_json->unprotected) {
        cJSON *unprotected_object = OpenAPI_object_convertToJSON(flat_jwe_json->unprotected);
        if (unprotected_object == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [unprotected]");
            goto end;
        }
        cJSON_AddItemToObject(item, "unprotected", unprotected_object);
        if (item->child == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [unprotected]");
            goto end;
        }
    }

    if (flat_jwe_json->header) {
        cJSON *header_object = OpenAPI_object_convertToJSON(flat_jwe_json->header);
        if (header_object == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [header]");
            goto end;
        }
        cJSON_AddItemToObject(item, "header", header_object);
        if (item->child == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [header]");
            goto end;
        }
    }

    if (flat_jwe_json->encrypted_key) {
        if (cJSON_AddStringToObject(item, "encrypted_key", flat_jwe_json->encrypted_key) == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [encrypted_key]");
            goto end;
        }
    }

    if (flat_jwe_json->aad) {
        if (cJSON_AddStringToObject(item, "aad", flat_jwe_json->aad) == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [aad]");
            goto end;
        }
    }

    if (flat_jwe_json->iv) {
        if (cJSON_AddStringToObject(item, "iv", flat_jwe_json->iv) == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [iv]");
            goto end;
        }
    }

    if (cJSON_AddStringToObject(item, "ciphertext", flat_jwe_json->ciphertext) == NULL) {
        ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [ciphertext]");
        goto end;
    }

    if (flat_jwe_json->tag) {
        if (cJSON_AddStringToObject(item, "tag", flat_jwe_json->tag) == NULL) {
            ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed [tag]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_parseFromJSON(cJSON *flat_jwe_jsonJSON)
{
    OpenAPI_flat_jwe_json_t *flat_jwe_json_local_var = NULL;
    cJSON *protected = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "protected");

    if (protected) {
        if (!cJSON_IsString(protected)) {
            ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [protected]");
            goto end;
        }
    }

    cJSON *unprotected = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "unprotected");

    OpenAPI_object_t *unprotected_local_object = NULL;
    if (unprotected) {
        unprotected_local_object = OpenAPI_object_parseFromJSON(unprotected);
    }

    cJSON *header = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "header");

    OpenAPI_object_t *header_local_object = NULL;
    if (header) {
        header_local_object = OpenAPI_object_parseFromJSON(header);
    }

    cJSON *encrypted_key = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "encrypted_key");

    if (encrypted_key) {
        if (!cJSON_IsString(encrypted_key)) {
            ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [encrypted_key]");
            goto end;
        }
    }

    cJSON *aad = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "aad");

    if (aad) {
        if (!cJSON_IsString(aad)) {
            ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [aad]");
            goto end;
        }
    }

    cJSON *iv = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "iv");

    if (iv) {
        if (!cJSON_IsString(iv)) {
            ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [iv]");
            goto end;
        }
    }

    cJSON *ciphertext = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "ciphertext");
    if (!ciphertext) {
        ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [ciphertext]");
        goto end;
    }


    if (!cJSON_IsString(ciphertext)) {
        ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [ciphertext]");
        goto end;
    }

    cJSON *tag = cJSON_GetObjectItemCaseSensitive(flat_jwe_jsonJSON, "tag");

    if (tag) {
        if (!cJSON_IsString(tag)) {
            ogs_error("OpenAPI_flat_jwe_json_parseFromJSON() failed [tag]");
            goto end;
        }
    }

    flat_jwe_json_local_var = OpenAPI_flat_jwe_json_create (
        protected ? ogs_strdup(protected->valuestring) : NULL,
        unprotected ? unprotected_local_object : NULL,
        header ? header_local_object : NULL,
        encrypted_key ? ogs_strdup(encrypted_key->valuestring) : NULL,
        aad ? ogs_strdup(aad->valuestring) : NULL,
        iv ? ogs_strdup(iv->valuestring) : NULL,
        ogs_strdup(ciphertext->valuestring),
        tag ? ogs_strdup(tag->valuestring) : NULL
        );

    return flat_jwe_json_local_var;
end:
    return NULL;
}

OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_copy(OpenAPI_flat_jwe_json_t *dst, OpenAPI_flat_jwe_json_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_flat_jwe_json_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_flat_jwe_json_convertToJSON() failed");
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

    OpenAPI_flat_jwe_json_free(dst);
    dst = OpenAPI_flat_jwe_json_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

