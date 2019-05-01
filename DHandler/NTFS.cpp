//
// Created by aseleznev on 24.04.2019.
//
#include "NTFS.h"

NTFS::NTFS(const HANDLE & hDevice, BYTE * bootRecordBuffer): FileSystem(hDevice)
{
    NTFS_BootRecord * NTFSBootRecord = (NTFS_BootRecord *) bootRecordBuffer;
    sectorsPerCluster = NTFSBootRecord->SectorsPerCluster;
    bytesPerSector = *((WORD*)NTFSBootRecord->BytesPerSector);
    bytesPerCluster = bytesPerSector * sectorsPerCluster;
    memcpy(OEM_ID, NTFSBootRecord->OEM_Name, sizeof(OEM_ID));
    totalClusters = NTFSBootRecord->TotalSectors/sectorsPerCluster;
}

BUFFER NTFS::FSReadFile()
{
	return NULL;
}

NTFS::~NTFS()
{
    CloseHandle(fileHandle);
}

