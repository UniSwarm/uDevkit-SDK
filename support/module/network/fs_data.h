#ifndef __FS_DATA_HEADER__
#define __FS_DATA_HEADER__
// ======== Struct declare ========
typedef struct
{
	const char *name;
	const char *type;
	const char *data;
	const unsigned int size;
} Fs_File;

typedef struct
{
	const Fs_File **files;
	const unsigned int count;
} Fs_FilesList;

#endif   //__FS_DATA_HEADER__
