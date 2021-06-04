
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "telescopic_mapping.h"

OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_create(
    char *telescopic_label,
    char *sepp_domain,
    char *foreign_fqdn
    )
{
    OpenAPI_telescopic_mapping_t *telescopic_mapping_local_var = OpenAPI_malloc(sizeof(OpenAPI_telescopic_mapping_t));
    if (!telescopic_mapping_local_var) {
        return NULL;
    }
    telescopic_mapping_local_var->telescopic_label = telescopic_label;
    telescopic_mapping_local_var->sepp_domain = sepp_domain;
    telescopic_mapping_local_var->foreign_fqdn = foreign_fqdn;

    return telescopic_mapping_local_var;
}

void OpenAPI_telescopic_mapping_free(OpenAPI_telescopic_mapping_t *telescopic_mapping)
{
    if (NULL == telescopic_mapping) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(telescopic_mapping->telescopic_label);
    ogs_free(telescopic_mapping->sepp_domain);
    ogs_free(telescopic_mapping->foreign_fqdn);
    ogs_free(telescopic_mapping);
}

cJSON *OpenAPI_telescopic_mapping_convertToJSON(OpenAPI_telescopic_mapping_t *telescopic_mapping)
{
    cJSON *item = NULL;

    if (telescopic_mapping == NULL) {
        ogs_error("OpenAPI_telescopic_mapping_convertToJSON() failed [TelescopicMapping]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (telescopic_mapping->telescopic_label) {
        if (cJSON_AddStringToObject(item, "telescopicLabel", telescopic_mapping->telescopic_label) == NULL) {
            ogs_error("OpenAPI_telescopic_mapping_convertToJSON() failed [telescopic_label]");
            goto end;
        }
    }

    if (telescopic_mapping->sepp_domain) {
        if (cJSON_AddStringToObject(item, "seppDomain", telescopic_mapping->sepp_domain) == NULL) {
            ogs_error("OpenAPI_telescopic_mapping_convertToJSON() failed [sepp_domain]");
            goto end;
        }
    }

    if (telescopic_mapping->foreign_fqdn) {
        if (cJSON_AddStringToObject(item, "foreignFqdn", telescopic_mapping->foreign_fqdn) == NULL) {
            ogs_error("OpenAPI_telescopic_mapping_convertToJSON() failed [foreign_fqdn]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_parseFromJSON(cJSON *telescopic_mappingJSON)
{
    OpenAPI_telescopic_mapping_t *telescopic_mapping_local_var = NULL;
    cJSON *telescopic_label = cJSON_GetObjectItemCaseSensitive(telescopic_mappingJSON, "telescopicLabel");

    if (telescopic_label) {
        if (!cJSON_IsString(telescopic_label)) {
            ogs_error("OpenAPI_telescopic_mapping_parseFromJSON() failed [telescopic_label]");
            goto end;
        }
    }

    cJSON *sepp_domain = cJSON_GetObjectItemCaseSensitive(telescopic_mappingJSON, "seppDomain");

    if (sepp_domain) {
        if (!cJSON_IsString(sepp_domain)) {
            ogs_error("OpenAPI_telescopic_mapping_parseFromJSON() failed [sepp_domain]");
            goto end;
        }
    }

    cJSON *foreign_fqdn = cJSON_GetObjectItemCaseSensitive(telescopic_mappingJSON, "foreignFqdn");

    if (foreign_fqdn) {
        if (!cJSON_IsString(foreign_fqdn)) {
            ogs_error("OpenAPI_telescopic_mapping_parseFromJSON() failed [foreign_fqdn]");
            goto end;
        }
    }

    telescopic_mapping_local_var = OpenAPI_telescopic_mapping_create (
        telescopic_label ? ogs_strdup(telescopic_label->valuestring) : NULL,
        sepp_domain ? ogs_strdup(sepp_domain->valuestring) : NULL,
        foreign_fqdn ? ogs_strdup(foreign_fqdn->valuestring) : NULL
        );

    return telescopic_mapping_local_var;
end:
    return NULL;
}

OpenAPI_telescopic_mapping_t *OpenAPI_telescopic_mapping_copy(OpenAPI_telescopic_mapping_t *dst, OpenAPI_telescopic_mapping_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_telescopic_mapping_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_telescopic_mapping_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_telescopic_mapping_free(dst);
    dst = OpenAPI_telescopic_mapping_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

