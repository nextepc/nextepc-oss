/*
 * n32f_reformatted_rsp_msg.h
 *
 *
 */

#ifndef _OpenAPI_n32f_reformatted_rsp_msg_H_
#define _OpenAPI_n32f_reformatted_rsp_msg_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "flat_jwe_json.h"
#include "flat_jws_json.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_n32f_reformatted_rsp_msg_s OpenAPI_n32f_reformatted_rsp_msg_t;
typedef struct OpenAPI_n32f_reformatted_rsp_msg_s {
    struct OpenAPI_flat_jwe_json_s *reformatted_data;
    OpenAPI_list_t *modifications_block;
} OpenAPI_n32f_reformatted_rsp_msg_t;

OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_create(
    OpenAPI_flat_jwe_json_t *reformatted_data,
    OpenAPI_list_t *modifications_block
    );
void OpenAPI_n32f_reformatted_rsp_msg_free(OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg);
OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_parseFromJSON(cJSON *n32f_reformatted_rsp_msgJSON);
cJSON *OpenAPI_n32f_reformatted_rsp_msg_convertToJSON(OpenAPI_n32f_reformatted_rsp_msg_t *n32f_reformatted_rsp_msg);
OpenAPI_n32f_reformatted_rsp_msg_t *OpenAPI_n32f_reformatted_rsp_msg_copy(OpenAPI_n32f_reformatted_rsp_msg_t *dst, OpenAPI_n32f_reformatted_rsp_msg_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_n32f_reformatted_rsp_msg_H_ */

