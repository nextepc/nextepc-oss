/*
 * n32f_error_type.h
 *
 *
 */

#ifndef _OpenAPI_n32f_error_type_H_
#define _OpenAPI_n32f_error_type_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_n32f_error_type_s OpenAPI_n32f_error_type_t;
typedef struct OpenAPI_n32f_error_type_s {
} OpenAPI_n32f_error_type_t;

OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_create(
    );
void OpenAPI_n32f_error_type_free(OpenAPI_n32f_error_type_t *n32f_error_type);
OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_parseFromJSON(cJSON *n32f_error_typeJSON);
cJSON *OpenAPI_n32f_error_type_convertToJSON(OpenAPI_n32f_error_type_t *n32f_error_type);
OpenAPI_n32f_error_type_t *OpenAPI_n32f_error_type_copy(OpenAPI_n32f_error_type_t *dst, OpenAPI_n32f_error_type_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_n32f_error_type_H_ */

