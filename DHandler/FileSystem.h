#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "Buffer.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#define BYTE_SIZE 8

class FileSystem
{
protected:
    HANDLE fileHandle;
    ULONGLONG totalClusters;
    BYTE OEM_ID[8];
    DWORD bytesPerSector;
    DWORD sectorsPerCluster;
    DWORD bytesPerCluster;
	DWORD clusterHeapOffset;
    LARGE_INTEGER * currentOffset;
public:
    FileSystem(const HANDLE & fHandle);
    void FileSystemInfo();
    Buffer ReadClusters(const ULONGLONG & startCluster, const DWORD & numberOfClusters);
	ULONGLONG GetTotalClusters();
    DWORD GetBytesPerCluster();
	ULONGLONG GetTotalSectors();
	static void PrintBuffer(Buffer fileSystemBuffer);
	virtual ULONGLONG GetClusterOffset();
    virtual Buffer FSReadFile() = 0;
    ~FileSystem();
};
typedef std::shared_ptr<FileSystem> pFileSystem;

/*
Not used
#undef max
template <class T>
T ReverseWord(T sourceWord)
{
	T reversedWord = 0;
	std::size_t wordSize = sizeof(T);
	T leftLimit = std::numeric_limits<T>::max(T) >> 1;
	leftLimit++;
	T rightLimit = leftLimit >> (wordSize - 1) * BYTE_SIZE;
	for (unsigned bytes = 0; bytes < wordSize; bytes++) {
		for (unsigned bits = 0; bits < BYTE_SIZE; bits++) {
			if (sourceWord & (rightLimit >> bits))
				reversedWord |= (leftLimit >> (bytes * BYTE_SIZE + bits));
		}
		rightLimit <<= BYTE_SIZE;
	};
	return reversedWord;
}
*/
#endif
