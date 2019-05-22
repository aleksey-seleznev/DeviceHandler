#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H
#include <windows.h>
#include <iostream>
#include <cwctype>
#include <mbstring.h>
#include <string.h>
#include "FileSystemFactory.h"
#define ERROR_VOLUME 1
#define ERROR_CLUSTER 2
#define BUFFER_SIZE MAX_PATH

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
	Buffer ReadFileSystem(HANDLE & hDevice, ULONGLONG & sectorOffset, DWORD & bytesToRead);
	pFileSystemHandler GetFileSystemHandler(WCHAR * volumeName);
    ~DeviceHandler();
};
#endif 
