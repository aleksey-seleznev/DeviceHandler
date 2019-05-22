#include "NTFS.h"

NTFS::NTFS(const HANDLE & hDevice, Buffer bootRecordBuffer): FileSystem(hDevice)
{
    NTFS_BootRecord * NTFSBootRecord = (NTFS_BootRecord *) bootRecordBuffer.GetBuffer();
    sectorsPerCluster = NTFSBootRecord->SectorsPerCluster;
    bytesPerSector = *((WORD*)NTFSBootRecord->BytesPerSector);
    bytesPerCluster = bytesPerSector * sectorsPerCluster;
    memcpy(OEM_ID, NTFSBootRecord->OEM_Name, sizeof(OEM_ID));
    totalClusters = NTFSBootRecord->TotalSectors/sectorsPerCluster;
	clusterHeapOffset = 2;
}

Buffer NTFS::FSReadFile()
{
	return Buffer();
}

NTFS::~NTFS()
{

}

