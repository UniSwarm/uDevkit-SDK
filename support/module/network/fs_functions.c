#include "fs_functions.h"

#include <string.h>

char test[100];

const Fs_File *getFile(char *fileName)
{
	int i;
	//const Fs_File *file_it=file_list.files[0];
	
	for(i=0; i<file_list.count; i++)
	{
		strcpy(test, file_list.files[i]->name);
		if(strcmp(file_list.files[i]->name, fileName)==0) return file_list.files[i];
	}
	return NULL;
}

