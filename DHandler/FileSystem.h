//
// Created by aseleznev on 23.04.2019.
//
#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <windows.h>
#include <iostream>
#include <limits>
#include <memory>
#define BYTE_SIZE 8
typedef std::unique_ptr<BYTE> BUFFER;

class FileSystem
{
protected:
    HANDLE fileHandle;
    ULONGLONG totalClusters;
    BYTE OEM_ID[8];
    DWORD bytesPerSector;
    DWORD sectorsPerCluster;
    DWORD bytesPerCluster;
    LARGE_INTEGER * currentOffset;
public:
    FileSystem(const HANDLE & fHandle);
    void FileSystemInfo();
    BYTE * ReadClusters(const ULONGLONG & startCluster, const DWORD & numberOfClusters);
	ULONGLONG GetTotalClusters();
    DWORD GetBytesPerCluster();
	ULONGLONG GetTotalSectors();
    virtual BUFFER FSReadFile() = 0;
    ~FileSystem();
};
typedef std::unique_ptr<FileSystem> PFileSystem;

#endif //FILESYSTEM_H
