/*
 * ie_location.h
 *
 *
 */

#ifndef _OpenAPI_ie_location_H_
#define _OpenAPI_ie_location_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ie_location_s OpenAPI_ie_location_t;
typedef struct OpenAPI_ie_location_s {
} OpenAPI_ie_location_t;

OpenAPI_ie_location_t *OpenAPI_ie_location_create(
    );
void OpenAPI_ie_location_free(OpenAPI_ie_location_t *ie_location);
OpenAPI_ie_location_t *OpenAPI_ie_location_parseFromJSON(cJSON *ie_locationJSON);
cJSON *OpenAPI_ie_location_convertToJSON(OpenAPI_ie_location_t *ie_location);
OpenAPI_ie_location_t *OpenAPI_ie_location_copy(OpenAPI_ie_location_t *dst, OpenAPI_ie_location_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ie_location_H_ */

