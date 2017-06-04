/**
 * @file fs_functions.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date June 2, 2017, 15:40 PM
 *
 * @brief Simple web file system
 */

#ifndef FS_FUNCTIONS_H
#define FS_FUNCTIONS_H

#include "fs_data.h"

const Fs_File *getFile(const Fs_FilesList *web_server_file_list, const char *fileName);

#endif // FS_FUNCTIONS_H
