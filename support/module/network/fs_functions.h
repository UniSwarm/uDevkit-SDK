/**
 * @file fs_functions.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date June 2, 2017, 15:40 PM
 *
 * @brief Simple web file system
 */

#ifndef FS_FUNCTIONS_H
#define FS_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fs_data.h"

const Fs_File *getFile(const Fs_FilesList *web_server_file_list, const char *fileName);

#ifdef __cplusplus
}
#endif

#endif  // FS_FUNCTIONS_H
