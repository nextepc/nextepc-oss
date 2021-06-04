/*
 * encoded_http_header_value.h
 *
 *
 */

#ifndef _OpenAPI_encoded_http_header_value_H_
#define _OpenAPI_encoded_http_header_value_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "index_to_encrypted_value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_encoded_http_header_value_s OpenAPI_encoded_http_header_value_t;
typedef struct OpenAPI_encoded_http_header_value_s {
    int enc_block_index;
} OpenAPI_encoded_http_header_value_t;

OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_create(
    int enc_block_index
    );
void OpenAPI_encoded_http_header_value_free(OpenAPI_encoded_http_header_value_t *encoded_http_header_value);
OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_parseFromJSON(cJSON *encoded_http_header_valueJSON);
cJSON *OpenAPI_encoded_http_header_value_convertToJSON(OpenAPI_encoded_http_header_value_t *encoded_http_header_value);
OpenAPI_encoded_http_header_value_t *OpenAPI_encoded_http_header_value_copy(OpenAPI_encoded_http_header_value_t *dst, OpenAPI_encoded_http_header_value_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_encoded_http_header_value_H_ */

