//
// Created by aseleznev on 24.04.2019.
//
#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H
#include <windows.h>
#include <iostream>
#include <cwctype>
#include <mbstring.h>
#include <string.h>
#include "NTFS.h"
#include "exFAT.h"
#define ERROR_VOLUME 1
#define ERROR_CLUSTER 2
#define BUFFER_SIZE MAX_PATH

typedef struct {
    BYTE Padding1[3];
    BYTE OEM_ID[8];
    BYTE BytesPerSector[2];
    BYTE SectorsPerCluster;
} CommonFileRecord;

class DeviceHandler {
private:
    HANDLE hDevice;
    DISK_GEOMETRY diskGeometry;
    WCHAR volumeList[BUFFER_SIZE];
    DWORD currentOffset;
    DWORD bytesReturned;
    DWORD errorCode;
    DWORD volumesNumber;
public:
    DeviceHandler();
    const DWORD & GetVolumesNumber();
    void SetVolumeName(WCHAR * volumeName, WCHAR volumeNumber);
    void GetSystemVolumes();
    void GetDiskGeometry(DISK_GEOMETRY & diskGeometry, HANDLE & hDevice);
    HANDLE CreateHandle(WCHAR * volumeName);
    BYTE * ReadFileSystem(HANDLE & hDevice, ULONGLONG & sectorOffset, DWORD & bytesToRead);
    PFileSystem GetFileSystem(WCHAR * volumeName);
    ~DeviceHandler();
};
#endif //DEVICEHANDLER_H
