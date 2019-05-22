#ifndef NTFS_H
#define NTFS_H
#include "FileSystem.h"

typedef struct
{
    BYTE Padding1[3];
    BYTE OEM_Name[8];
    BYTE BytesPerSector[2];
    BYTE SectorsPerCluster;
    BYTE Padding2[26];
    ULONGLONG TotalSectors;
} NTFS_BootRecord;

class NTFS : public FileSystem
{
public:
    NTFS(const HANDLE & hDevice, Buffer bootRecordBuffer);
    virtual Buffer FSReadFile();
    ~NTFS();
};

#endif
