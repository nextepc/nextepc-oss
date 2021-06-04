/*
 * data_to_integrity_protect_block.h
 *
 *
 */

#ifndef _OpenAPI_data_to_integrity_protect_block_H_
#define _OpenAPI_data_to_integrity_protect_block_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "http_header.h"
#include "http_payload.h"
#include "meta_data.h"
#include "request_line.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_data_to_integrity_protect_block_s OpenAPI_data_to_integrity_protect_block_t;
typedef struct OpenAPI_data_to_integrity_protect_block_s {
    struct OpenAPI_meta_data_s *meta_data;
    struct OpenAPI_request_line_s *request_line;
    char *status_line;
    OpenAPI_list_t *headers;
    OpenAPI_list_t *payload;
} OpenAPI_data_to_integrity_protect_block_t;

OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_create(
    OpenAPI_meta_data_t *meta_data,
    OpenAPI_request_line_t *request_line,
    char *status_line,
    OpenAPI_list_t *headers,
    OpenAPI_list_t *payload
    );
void OpenAPI_data_to_integrity_protect_block_free(OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block);
OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_parseFromJSON(cJSON *data_to_integrity_protect_blockJSON);
cJSON *OpenAPI_data_to_integrity_protect_block_convertToJSON(OpenAPI_data_to_integrity_protect_block_t *data_to_integrity_protect_block);
OpenAPI_data_to_integrity_protect_block_t *OpenAPI_data_to_integrity_protect_block_copy(OpenAPI_data_to_integrity_protect_block_t *dst, OpenAPI_data_to_integrity_protect_block_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_data_to_integrity_protect_block_H_ */

