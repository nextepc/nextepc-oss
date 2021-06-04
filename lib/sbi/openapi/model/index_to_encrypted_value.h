/*
 * index_to_encrypted_value.h
 *
 *
 */

#ifndef _OpenAPI_index_to_encrypted_value_H_
#define _OpenAPI_index_to_encrypted_value_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_index_to_encrypted_value_s OpenAPI_index_to_encrypted_value_t;
typedef struct OpenAPI_index_to_encrypted_value_s {
    int enc_block_index;
} OpenAPI_index_to_encrypted_value_t;

OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_create(
    int enc_block_index
    );
void OpenAPI_index_to_encrypted_value_free(OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value);
OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_parseFromJSON(cJSON *index_to_encrypted_valueJSON);
cJSON *OpenAPI_index_to_encrypted_value_convertToJSON(OpenAPI_index_to_encrypted_value_t *index_to_encrypted_value);
OpenAPI_index_to_encrypted_value_t *OpenAPI_index_to_encrypted_value_copy(OpenAPI_index_to_encrypted_value_t *dst, OpenAPI_index_to_encrypted_value_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_index_to_encrypted_value_H_ */

