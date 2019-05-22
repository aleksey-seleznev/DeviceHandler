#include "FileSystem.h"

FileSystem::FileSystem(const HANDLE & fHandle)
{
    fileHandle = fHandle;
    totalClusters = 0;
    OEM_ID[8] = {0};
    bytesPerSector = 0;
    sectorsPerCluster = 0;
    bytesPerCluster = 0;
	clusterHeapOffset = 0;
    currentOffset = NULL;
}

void FileSystem::FileSystemInfo()
{
    printf("File system name:%s\n", OEM_ID);
    wprintf(L"Bytes per cluster:%lu\n", bytesPerCluster);
    wprintf(L"Bytes per sector:%lu\n", bytesPerSector);
    wprintf(L"Sectors per cluster:%lu\n",sectorsPerCluster);
    wprintf(L"Total clusters:%llu\n", totalClusters);
}

Buffer FileSystem::ReadClusters(const ULONGLONG & startCluster, const DWORD & numberOfClusters)
{
	if (startCluster >= 0 and startCluster <= totalClusters)
	{
		DWORD errorCode;
		DWORD bytesReturned = 0;
		DWORD bytesToRead = bytesPerCluster * numberOfClusters;
		Buffer readBuffer(new BYTE[bytesToRead], bytesToRead);
		BYTE * outBuffer = readBuffer.GetBuffer();
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = startCluster * bytesPerCluster;
		if (!SetFilePointerEx(fileHandle, sectorOffset, currentOffset, FILE_BEGIN)) {
			errorCode = GetLastError();
			CloseHandle(fileHandle);
			exit(errorCode);
		}
		bool readResult = ReadFile(fileHandle, outBuffer, bytesToRead, &bytesReturned, NULL);
		if (!readResult || bytesReturned != bytesToRead) {
			errorCode = GetLastError();
			CloseHandle(fileHandle);
			exit(errorCode);
		}
		return readBuffer;
	}
	else
		return Buffer();
}

Buffer FileSystem::FSReadFile()
{
	return Buffer();
}

ULONGLONG FileSystem::GetTotalClusters()
{
    return totalClusters;
}

DWORD FileSystem::GetBytesPerCluster()
{
    return bytesPerCluster;
}

ULONGLONG FileSystem::GetTotalSectors()
{
    return totalClusters * sectorsPerCluster;
}

void FileSystem::PrintBuffer(Buffer fileSystemBuffer)
{
	std::size_t bufferSize = fileSystemBuffer.GetBufferSize();
	BYTE * bufferIterator = fileSystemBuffer.GetBuffer();
	for (std::size_t count = 0; count < bufferSize; count++)
	{
		std::cout << std::setw(2) << std::setfill('0') << std::hex << DWORD(*bufferIterator) << " ";
		bufferIterator++;
	}
}

ULONGLONG FileSystem::GetClusterOffset()
{
	return clusterHeapOffset;
}

FileSystem::~FileSystem()
{
	fileHandle = NULL;
}

