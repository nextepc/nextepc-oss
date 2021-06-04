/*
 * meta_data.h
 *
 *
 */

#ifndef _OpenAPI_meta_data_H_
#define _OpenAPI_meta_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_meta_data_s OpenAPI_meta_data_t;
typedef struct OpenAPI_meta_data_s {
    char *n32f_context_id;
    char *message_id;
    char *authorized_ipx_id;
} OpenAPI_meta_data_t;

OpenAPI_meta_data_t *OpenAPI_meta_data_create(
    char *n32f_context_id,
    char *message_id,
    char *authorized_ipx_id
    );
void OpenAPI_meta_data_free(OpenAPI_meta_data_t *meta_data);
OpenAPI_meta_data_t *OpenAPI_meta_data_parseFromJSON(cJSON *meta_dataJSON);
cJSON *OpenAPI_meta_data_convertToJSON(OpenAPI_meta_data_t *meta_data);
OpenAPI_meta_data_t *OpenAPI_meta_data_copy(OpenAPI_meta_data_t *dst, OpenAPI_meta_data_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_meta_data_H_ */

