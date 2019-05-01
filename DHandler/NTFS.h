//
// Created by aseleznev on 24.04.2019.
//
#ifndef NTFS_H
#define NTFS_H
#include "FileSystem.h"
#define _NTFS "NTFS    "

typedef struct
{
    BYTE Padding1[3];
    BYTE OEM_Name[8];
    BYTE BytesPerSector[2];
    BYTE SectorsPerCluster;
    BYTE Padding2[26];
    ULONGLONG TotalSectors; // Количество секторов в файловой системе
} NTFS_BootRecord;

class NTFS : public FileSystem
{
public:
    NTFS(const HANDLE & hDevice, BYTE * bootRecordBuffer);
    virtual BUFFER FSReadFile();
    ~NTFS();
};

#endif //NTFS_H
