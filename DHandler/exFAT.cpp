#include "exFAT.h"

exFAT::exFAT(const HANDLE & hDevice, Buffer bootRecordBuffer): FileSystem(hDevice)
{
    exFAT_BootRecord * exFATBootRecord = (exFAT_BootRecord *) bootRecordBuffer.GetBuffer();
    totalClusters = exFATBootRecord->TotalClusters;
    memcpy(OEM_ID, exFATBootRecord->OEM_Name, sizeof(OEM_ID));
    bytesPerSector = pow(2, exFATBootRecord->SectorFactor);
    sectorsPerCluster = pow(2, exFATBootRecord->ClusterFactor);
    bytesPerCluster = bytesPerSector * sectorsPerCluster;
	clusterHeapOffset = round(exFATBootRecord->ClusterHeapOffset * bytesPerSector) / bytesPerCluster - 2;
}

Buffer exFAT::FSReadFile()
{
	return Buffer();
}

exFAT::~exFAT()
{

}

