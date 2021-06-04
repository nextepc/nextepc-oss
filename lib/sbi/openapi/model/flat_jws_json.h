/*
 * flat_jws_json.h
 *
 *
 */

#ifndef _OpenAPI_flat_jws_json_H_
#define _OpenAPI_flat_jws_json_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_flat_jws_json_s OpenAPI_flat_jws_json_t;
typedef struct OpenAPI_flat_jws_json_s {
    char *payload;
    char *protected;
    OpenAPI_object_t *header;
    char *signature;
} OpenAPI_flat_jws_json_t;

OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_create(
    char *payload,
    char *protected,
    OpenAPI_object_t *header,
    char *signature
    );
void OpenAPI_flat_jws_json_free(OpenAPI_flat_jws_json_t *flat_jws_json);
OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_parseFromJSON(cJSON *flat_jws_jsonJSON);
cJSON *OpenAPI_flat_jws_json_convertToJSON(OpenAPI_flat_jws_json_t *flat_jws_json);
OpenAPI_flat_jws_json_t *OpenAPI_flat_jws_json_copy(OpenAPI_flat_jws_json_t *dst, OpenAPI_flat_jws_json_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_flat_jws_json_H_ */

