//
// Created by aseleznev on 24.04.2019.
//
#include "exFAT.h"

exFAT::exFAT(const HANDLE & hDevice, BYTE * bootRecordBuffer): FileSystem(hDevice)
{
    exFAT_BootRecord * exFATBootRecord = (exFAT_BootRecord *) bootRecordBuffer;
    totalClusters = exFATBootRecord->TotalClusters;
    memcpy(OEM_ID, exFATBootRecord->OEM_Name, sizeof(OEM_ID));
    bytesPerSector = pow(2, exFATBootRecord->SectorFactor);
    sectorsPerCluster = pow(2, exFATBootRecord->ClusterFactor);
    bytesPerCluster = bytesPerSector * sectorsPerCluster;
}

BUFFER exFAT::FSReadFile()
{
	return NULL;
}

exFAT::~exFAT()
{
    CloseHandle(fileHandle);
}

