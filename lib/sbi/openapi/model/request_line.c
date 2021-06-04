
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "request_line.h"

OpenAPI_request_line_t *OpenAPI_request_line_create(
    OpenAPI_http_method_e method,
    OpenAPI_uri_scheme_e scheme,
    char *authority,
    char *path,
    char *protocol_version,
    char *query_fragment
    )
{
    OpenAPI_request_line_t *request_line_local_var = OpenAPI_malloc(sizeof(OpenAPI_request_line_t));
    if (!request_line_local_var) {
        return NULL;
    }
    request_line_local_var->method = method;
    request_line_local_var->scheme = scheme;
    request_line_local_var->authority = authority;
    request_line_local_var->path = path;
    request_line_local_var->protocol_version = protocol_version;
    request_line_local_var->query_fragment = query_fragment;

    return request_line_local_var;
}

void OpenAPI_request_line_free(OpenAPI_request_line_t *request_line)
{
    if (NULL == request_line) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(request_line->authority);
    ogs_free(request_line->path);
    ogs_free(request_line->protocol_version);
    ogs_free(request_line->query_fragment);
    ogs_free(request_line);
}

cJSON *OpenAPI_request_line_convertToJSON(OpenAPI_request_line_t *request_line)
{
    cJSON *item = NULL;

    if (request_line == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [RequestLine]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (cJSON_AddStringToObject(item, "method", OpenAPI_http_method_ToString(request_line->method)) == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [method]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "scheme", OpenAPI_uri_scheme_ToString(request_line->scheme)) == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [scheme]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "authority", request_line->authority) == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [authority]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "path", request_line->path) == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [path]");
        goto end;
    }

    if (cJSON_AddStringToObject(item, "protocolVersion", request_line->protocol_version) == NULL) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed [protocol_version]");
        goto end;
    }

    if (request_line->query_fragment) {
        if (cJSON_AddStringToObject(item, "queryFragment", request_line->query_fragment) == NULL) {
            ogs_error("OpenAPI_request_line_convertToJSON() failed [query_fragment]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_request_line_t *OpenAPI_request_line_parseFromJSON(cJSON *request_lineJSON)
{
    OpenAPI_request_line_t *request_line_local_var = NULL;
    cJSON *method = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "method");
    if (!method) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [method]");
        goto end;
    }

    OpenAPI_http_method_e methodVariable;

    if (!cJSON_IsString(method)) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [method]");
        goto end;
    }
    methodVariable = OpenAPI_http_method_FromString(method->valuestring);

    cJSON *scheme = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "scheme");
    if (!scheme) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [scheme]");
        goto end;
    }

    OpenAPI_uri_scheme_e schemeVariable;

    if (!cJSON_IsString(scheme)) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [scheme]");
        goto end;
    }
    schemeVariable = OpenAPI_uri_scheme_FromString(scheme->valuestring);

    cJSON *authority = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "authority");
    if (!authority) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [authority]");
        goto end;
    }


    if (!cJSON_IsString(authority)) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [authority]");
        goto end;
    }

    cJSON *path = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "path");
    if (!path) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [path]");
        goto end;
    }


    if (!cJSON_IsString(path)) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [path]");
        goto end;
    }

    cJSON *protocol_version = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "protocolVersion");
    if (!protocol_version) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [protocol_version]");
        goto end;
    }


    if (!cJSON_IsString(protocol_version)) {
        ogs_error("OpenAPI_request_line_parseFromJSON() failed [protocol_version]");
        goto end;
    }

    cJSON *query_fragment = cJSON_GetObjectItemCaseSensitive(request_lineJSON, "queryFragment");

    if (query_fragment) {
        if (!cJSON_IsString(query_fragment)) {
            ogs_error("OpenAPI_request_line_parseFromJSON() failed [query_fragment]");
            goto end;
        }
    }

    request_line_local_var = OpenAPI_request_line_create (
        methodVariable,
        schemeVariable,
        ogs_strdup(authority->valuestring),
        ogs_strdup(path->valuestring),
        ogs_strdup(protocol_version->valuestring),
        query_fragment ? ogs_strdup(query_fragment->valuestring) : NULL
        );

    return request_line_local_var;
end:
    return NULL;
}

OpenAPI_request_line_t *OpenAPI_request_line_copy(OpenAPI_request_line_t *dst, OpenAPI_request_line_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_request_line_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_request_line_convertToJSON() failed");
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

    OpenAPI_request_line_free(dst);
    dst = OpenAPI_request_line_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

