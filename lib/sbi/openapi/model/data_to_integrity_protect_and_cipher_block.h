/*
 * data_to_integrity_protect_and_cipher_block.h
 *
 *
 */

#ifndef _OpenAPI_data_to_integrity_protect_and_cipher_block_H_
#define _OpenAPI_data_to_integrity_protect_and_cipher_block_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "any_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_data_to_integrity_protect_and_cipher_block_s OpenAPI_data_to_integrity_protect_and_cipher_block_t;
typedef struct OpenAPI_data_to_integrity_protect_and_cipher_block_s {
    OpenAPI_list_t *data_to_encrypt;
} OpenAPI_data_to_integrity_protect_and_cipher_block_t;

OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_create(
    OpenAPI_list_t *data_to_encrypt
    );
void OpenAPI_data_to_integrity_protect_and_cipher_block_free(OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block);
OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_parseFromJSON(cJSON *data_to_integrity_protect_and_cipher_blockJSON);
cJSON *OpenAPI_data_to_integrity_protect_and_cipher_block_convertToJSON(OpenAPI_data_to_integrity_protect_and_cipher_block_t *data_to_integrity_protect_and_cipher_block);
OpenAPI_data_to_integrity_protect_and_cipher_block_t *OpenAPI_data_to_integrity_protect_and_cipher_block_copy(OpenAPI_data_to_integrity_protect_and_cipher_block_t *dst, OpenAPI_data_to_integrity_protect_and_cipher_block_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_data_to_integrity_protect_and_cipher_block_H_ */

