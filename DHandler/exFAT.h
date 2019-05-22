#ifndef EXFAT_H
#define EXFAT_H
#include <cmath>
#include "FileSystem.h"

typedef struct
{
    BYTE Padding1[3];
    BYTE OEM_Name[8];
    BYTE Padding2[61];
    ULONGLONG TotalSectors;
    DWORD FATStartSector;
    DWORD FATSizeInSectors;
    DWORD ClusterHeapOffset;
    DWORD TotalClusters;
	DWORD RootDirCluster;
    BYTE Padding3[8];
    BYTE SectorFactor;
    BYTE ClusterFactor;
} exFAT_BootRecord;

class exFAT: public FileSystem
{
public:
    exFAT(const HANDLE & hDevice, Buffer bootRecordBuffer);
    virtual Buffer FSReadFile();
    ~exFAT();
};
#endif
