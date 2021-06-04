/*
 * request_line.h
 *
 *
 */

#ifndef _OpenAPI_request_line_H_
#define _OpenAPI_request_line_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "http_method.h"
#include "uri_scheme.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_request_line_s OpenAPI_request_line_t;
typedef struct OpenAPI_request_line_s {
    OpenAPI_http_method_e method;
    OpenAPI_uri_scheme_e scheme;
    char *authority;
    char *path;
    char *protocol_version;
    char *query_fragment;
} OpenAPI_request_line_t;

OpenAPI_request_line_t *OpenAPI_request_line_create(
    OpenAPI_http_method_e method,
    OpenAPI_uri_scheme_e scheme,
    char *authority,
    char *path,
    char *protocol_version,
    char *query_fragment
    );
void OpenAPI_request_line_free(OpenAPI_request_line_t *request_line);
OpenAPI_request_line_t *OpenAPI_request_line_parseFromJSON(cJSON *request_lineJSON);
cJSON *OpenAPI_request_line_convertToJSON(OpenAPI_request_line_t *request_line);
OpenAPI_request_line_t *OpenAPI_request_line_copy(OpenAPI_request_line_t *dst, OpenAPI_request_line_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_request_line_H_ */

