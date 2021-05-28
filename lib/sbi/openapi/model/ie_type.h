/*
 * ie_type.h
 *
 *
 */

#ifndef _OpenAPI_ie_type_H_
#define _OpenAPI_ie_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_ie_type_s OpenAPI_ie_type_t;
typedef struct OpenAPI_ie_type_s {
} OpenAPI_ie_type_t;

OpenAPI_ie_type_t *OpenAPI_ie_type_create(
    );
void OpenAPI_ie_type_free(OpenAPI_ie_type_t *ie_type);
OpenAPI_ie_type_t *OpenAPI_ie_type_parseFromJSON(cJSON *ie_typeJSON);
cJSON *OpenAPI_ie_type_convertToJSON(OpenAPI_ie_type_t *ie_type);
OpenAPI_ie_type_t *OpenAPI_ie_type_copy(OpenAPI_ie_type_t *dst, OpenAPI_ie_type_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_ie_type_H_ */

