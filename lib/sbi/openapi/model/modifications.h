/*
 * modifications.h
 *
 *
 */

#ifndef _OpenAPI_modifications_H_
#define _OpenAPI_modifications_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "patch_item.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_modifications_s OpenAPI_modifications_t;
typedef struct OpenAPI_modifications_s {
    char *identity;
    OpenAPI_list_t *operations;
} OpenAPI_modifications_t;

OpenAPI_modifications_t *OpenAPI_modifications_create(
    char *identity,
    OpenAPI_list_t *operations
    );
void OpenAPI_modifications_free(OpenAPI_modifications_t *modifications);
OpenAPI_modifications_t *OpenAPI_modifications_parseFromJSON(cJSON *modificationsJSON);
cJSON *OpenAPI_modifications_convertToJSON(OpenAPI_modifications_t *modifications);
OpenAPI_modifications_t *OpenAPI_modifications_copy(OpenAPI_modifications_t *dst, OpenAPI_modifications_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_modifications_H_ */

