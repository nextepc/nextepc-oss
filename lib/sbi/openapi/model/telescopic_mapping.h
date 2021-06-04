/*
 * telescopic_mapping.h
 *
 *
 */

#ifndef _OpenAPI_telescopic_mapping_H_
#define _OpenAPI_telescopic_mapping_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_telescopic_mapping_s OpenAPI_telescopic_mapping_t;
typedef struct OpenAPI_telescopic_mapping_s {
    char *telescopic_label;
    char *sepp_domain;
    char *foreign_fqdn;
} OpenAPI_telescopic_mapping_t;

OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_create(
    char *telescopic_label,
    char *sepp_domain,
    char *foreign_fqdn
    );
void OpenAPI_telescopic_mapping_free(OpenAPI_telescopic_mapping_t *telescopic_mapping);
OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_parseFromJSON(cJSON *telescopic_mappingJSON);
cJSON *OpenAPI_telescopic_mapping_convertToJSON(OpenAPI_telescopic_mapping_t *telescopic_mapping);
OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_copy(OpenAPI_telescopic_mapping_t *dst, OpenAPI_telescopic_mapping_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_telescopic_mapping_H_ */

