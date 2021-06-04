/*
 * flat_jwe_json.h
 *
 *
 */

#ifndef _OpenAPI_flat_jwe_json_H_
#define _OpenAPI_flat_jwe_json_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_flat_jwe_json_s OpenAPI_flat_jwe_json_t;
typedef struct OpenAPI_flat_jwe_json_s {
    char *protected;
    OpenAPI_object_t *unprotected;
    OpenAPI_object_t *header;
    char *encrypted_key;
    char *aad;
    char *iv;
    char *ciphertext;
    char *tag;
} OpenAPI_flat_jwe_json_t;

OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_create(
    char *protected,
    OpenAPI_object_t *unprotected,
    OpenAPI_object_t *header,
    char *encrypted_key,
    char *aad,
    char *iv,
    char *ciphertext,
    char *tag
    );
void OpenAPI_flat_jwe_json_free(OpenAPI_flat_jwe_json_t *flat_jwe_json);
OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_parseFromJSON(cJSON *flat_jwe_jsonJSON);
cJSON *OpenAPI_flat_jwe_json_convertToJSON(OpenAPI_flat_jwe_json_t *flat_jwe_json);
OpenAPI_flat_jwe_json_t *OpenAPI_flat_jwe_json_copy(OpenAPI_flat_jwe_json_t *dst, OpenAPI_flat_jwe_json_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_flat_jwe_json_H_ */

