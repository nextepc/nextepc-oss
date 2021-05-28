/*
 * security_capability.h
 *
 *
 */

#ifndef _OpenAPI_security_capability_H_
#define _OpenAPI_security_capability_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_security_capability_s OpenAPI_security_capability_t;
typedef struct OpenAPI_security_capability_s {
} OpenAPI_security_capability_t;

OpenAPI_security_capability_t *OpenAPI_security_capability_create(
    );
void OpenAPI_security_capability_free(OpenAPI_security_capability_t *security_capability);
OpenAPI_security_capability_t *OpenAPI_security_capability_parseFromJSON(cJSON *security_capabilityJSON);
cJSON *OpenAPI_security_capability_convertToJSON(OpenAPI_security_capability_t *security_capability);
OpenAPI_security_capability_t *OpenAPI_security_capability_copy(OpenAPI_security_capability_t *dst, OpenAPI_security_capability_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_security_capability_H_ */

