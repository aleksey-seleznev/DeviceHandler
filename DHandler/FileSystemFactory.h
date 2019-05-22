#ifndef FILESYSTEMFACTORY_H
#define FILESYSTEMFACTORY_H
#include "FileSystemHandler.h"

typedef struct {
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	BYTE BytesPerSector[2];
	BYTE SectorsPerCluster;
} FileSystemRecord, * pFileSystemRecord;

class FileSystemFactory
{
public:
	FileSystemFactory();
	static FileSystemHandler * CreateFileSystemHandler(const HANDLE & hDevice, Buffer recordBuffer);
	~FileSystemFactory();
};

#endif

