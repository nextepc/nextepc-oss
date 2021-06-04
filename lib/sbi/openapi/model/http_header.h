/*
 * http_header.h
 *
 *
 */

#ifndef _OpenAPI_http_header_H_
#define _OpenAPI_http_header_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "encoded_http_header_value.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_http_header_s OpenAPI_http_header_t;
typedef struct OpenAPI_http_header_s {
    char *header;
    struct OpenAPI_encoded_http_header_value_s *value;
} OpenAPI_http_header_t;

OpenAPI_http_header_t *OpenAPI_http_header_create(
    char *header,
    OpenAPI_encoded_http_header_value_t *value
    );
void OpenAPI_http_header_free(OpenAPI_http_header_t *http_header);
OpenAPI_http_header_t *OpenAPI_http_header_parseFromJSON(cJSON *http_headerJSON);
cJSON *OpenAPI_http_header_convertToJSON(OpenAPI_http_header_t *http_header);
OpenAPI_http_header_t *OpenAPI_http_header_copy(OpenAPI_http_header_t *dst, OpenAPI_http_header_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_http_header_H_ */

