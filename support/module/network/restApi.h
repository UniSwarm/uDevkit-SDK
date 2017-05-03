#ifndef __REST_API_HEADER__
#define __REST_API_HEADER__

#include "http.h"

void rest_api_init();
void rest_api_exec(HTTP_PARSE_RESULT *http_parse_result, char *buffer);

#endif   //__REST_API_HEADER__
