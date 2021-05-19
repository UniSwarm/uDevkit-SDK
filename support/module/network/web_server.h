/**
 * @file web_server.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date June 2, 2016, 15:40 PM
 *
 * @brief HTTP protocol parsing and formating
 */

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "fs_data.h"
#include "http.h"
#include "json.h"

void web_server_init(void);
void web_server_task(void);

void web_server_setRestApi(void (*restApi)(char *url, HTTP_QUERRY_TYPE code, char *buffer));
void web_server_setRootFS(const Fs_FilesList *file_list);

#endif  // WEB_SERVER_H
