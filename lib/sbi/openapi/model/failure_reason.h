/*
 * failure_reason.h
 *
 *
 */

#ifndef _OpenAPI_failure_reason_H_
#define _OpenAPI_failure_reason_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_failure_reason_s OpenAPI_failure_reason_t;
typedef struct OpenAPI_failure_reason_s {
} OpenAPI_failure_reason_t;

OpenAPI_failure_reason_t *OpenAPI_failure_reason_create(
    );
void OpenAPI_failure_reason_free(OpenAPI_failure_reason_t *failure_reason);
OpenAPI_failure_reason_t *OpenAPI_failure_reason_parseFromJSON(cJSON *failure_reasonJSON);
cJSON *OpenAPI_failure_reason_convertToJSON(OpenAPI_failure_reason_t *failure_reason);
OpenAPI_failure_reason_t *OpenAPI_failure_reason_copy(OpenAPI_failure_reason_t *dst, OpenAPI_failure_reason_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_failure_reason_H_ */

