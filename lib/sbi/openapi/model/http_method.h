/*
 * http_method.h
 *
 *
 */

#ifndef _OpenAPI_http_method_H_
#define _OpenAPI_http_method_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_http_method_s OpenAPI_http_method_t;
typedef struct OpenAPI_http_method_s {
} OpenAPI_http_method_t;

OpenAPI_http_method_t *OpenAPI_http_method_create(
    );
void OpenAPI_http_method_free(OpenAPI_http_method_t *http_method);
OpenAPI_http_method_t *OpenAPI_http_method_parseFromJSON(cJSON *http_methodJSON);
cJSON *OpenAPI_http_method_convertToJSON(OpenAPI_http_method_t *http_method);
OpenAPI_http_method_t *OpenAPI_http_method_copy(OpenAPI_http_method_t *dst, OpenAPI_http_method_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_http_method_H_ */

