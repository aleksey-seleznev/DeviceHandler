#ifndef FAT_H
#define FAT_H
#include <cmath>
#include "FileSystem.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_Name[8];
	BYTE BytesPerSector[2];
	BYTE SectorsPerCluster;
	BYTE ReservedSectors[2];
	BYTE Padding2[16];
	ULONGLONG TotalSectors;
} FAT_BootRecord;

class FAT : public FileSystem
{
public:
	FAT(const HANDLE & hDevice, Buffer bootRecordBuffer);
	virtual Buffer FSReadFile();
	~FAT();
};

#endif
