/**
 * @file fs_functions.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date June 2, 2017, 15:40 PM
 *
 * @brief Simple web file system
 */

#include "fs_functions.h"

#include <string.h>

const Fs_File *getFile(const Fs_FilesList *file_list, const char *fileName)
{
	int i;

	for (i=0; i<file_list->count; i++)
	{
		if (strcmp(file_list->files[i]->name, fileName)==0)
            return file_list->files[i];
	}
	return NULL;
}
