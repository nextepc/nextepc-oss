/*
 * http_payload.h
 *
 *
 */

#ifndef _OpenAPI_http_payload_H_
#define _OpenAPI_http_payload_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "ie_location.h"
#include "object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_http_payload_s OpenAPI_http_payload_t;
typedef struct OpenAPI_http_payload_s {
    char *ie_path;
    OpenAPI_ie_location_e ie_value_location;
    OpenAPI_object_t *value;
} OpenAPI_http_payload_t;

OpenAPI_http_payload_t *OpenAPI_http_payload_create(
    char *ie_path,
    OpenAPI_ie_location_e ie_value_location,
    OpenAPI_object_t *value
    );
void OpenAPI_http_payload_free(OpenAPI_http_payload_t *http_payload);
OpenAPI_http_payload_t *OpenAPI_http_payload_parseFromJSON(cJSON *http_payloadJSON);
cJSON *OpenAPI_http_payload_convertToJSON(OpenAPI_http_payload_t *http_payload);
OpenAPI_http_payload_t *OpenAPI_http_payload_copy(OpenAPI_http_payload_t *dst, OpenAPI_http_payload_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_http_payload_H_ */

