#include "FAT.h"

FAT::FAT(const HANDLE & hDevice, Buffer bootRecordBuffer) : FileSystem(hDevice)
{
	FAT_BootRecord * FATBootRecord = (FAT_BootRecord *)bootRecordBuffer.GetBuffer();
	sectorsPerCluster = FATBootRecord->SectorsPerCluster;
	bytesPerSector = *((WORD*)FATBootRecord->BytesPerSector);
	bytesPerCluster = bytesPerSector * sectorsPerCluster;
	memcpy(OEM_ID, FATBootRecord->OEM_Name, sizeof(OEM_ID));
	totalClusters = FATBootRecord->TotalSectors / sectorsPerCluster;
	clusterHeapOffset = round(*((WORD*)FATBootRecord->ReservedSectors) * bytesPerSector) / bytesPerCluster;
}

Buffer FAT::FSReadFile()
{
	return Buffer();
}

FAT::~FAT()
{
	
}

