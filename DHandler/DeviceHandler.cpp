//
// Created by aseleznev on 24.04.2019.
//
#include "DeviceHandler.h"

DeviceHandler::DeviceHandler()
{
    hDevice = NULL;
    diskGeometry = DISK_GEOMETRY();
	volumeList[BUFFER_SIZE] = {NULL};
    currentOffset = 0;
    bytesReturned = 0;
    errorCode = 0;
    volumesNumber = 0;
}

void DeviceHandler::SetVolumeName(WCHAR * volumeName, WCHAR volumeCharacter)
{
	WCHAR * volumeIterator = volumeList;
	WCHAR upperCharacter = std::towupper(volumeCharacter);
	for (unsigned i = 0; i < BUFFER_SIZE && *volumeIterator != upperCharacter; i++) {
		volumeIterator++;
	}
	WCHAR * volume = wcschr(volumeList, upperCharacter);
	if (volumeIterator == NULL) {
		std::cout << "Error volume name.";
		exit(ERROR_VOLUME);
	}
    wcscpy(volumeName, L"\\\\.\\");
    wcsncpy(volumeName + 4, volumeIterator, 2);
}
const DWORD & DeviceHandler::GetVolumesNumber()
{
    return volumesNumber;
}

void PrintStorageDeviceInfo(STORAGE_DEVICE_NUMBER * storageDevice)
{
    std::cout << "\t- Physical device number: " << storageDevice->DeviceNumber << std::endl;
    std::cout << "\t- Device parition number: " << storageDevice->PartitionNumber << std::endl;
    std::cout << "\t- Device type: " << storageDevice->DeviceType << std::endl;
}

void DeviceHandler::GetSystemVolumes()
{
    DWORD bufferSize = BUFFER_SIZE, driveType;
    WCHAR * volumeIterator;
    GetLogicalDriveStringsW(bufferSize, (LPWSTR)volumeList);
    volumeIterator = volumeList;
    while (*volumeIterator) {
        volumesNumber++;
        driveType = GetDriveTypeW(volumeIterator);
        if(driveType == DRIVE_REMOVABLE or driveType == DRIVE_FIXED) {
            WCHAR volumeName[8] = L"\\\\.\\";
            wcsncpy(volumeName + 4, volumeIterator, 2);
            HANDLE diskHandle = CreateHandle(volumeName);
            STORAGE_DEVICE_NUMBER storageDevice = {0};
            DWORD bytesReturned;
            if (DeviceIoControl(diskHandle, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0,
                                &storageDevice, sizeof(STORAGE_DEVICE_NUMBER), &bytesReturned, NULL)) {
                std::wcout << volumesNumber << L") Volume " << *volumeIterator << L":\\ information:" << std::endl;
                PrintStorageDeviceInfo(&storageDevice);
            }
            else wprintf(L"Error while reading volume: %s.\n", volumeIterator);
            CloseHandle(diskHandle);
        }
        volumeIterator += wcslen(volumeIterator) + 1;
    }
}

void DeviceHandler::GetDiskGeometry(DISK_GEOMETRY & diskGeometry, HANDLE & hDevice)
{
    if(!DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0,
                        &diskGeometry, sizeof(diskGeometry), &bytesReturned, NULL)){
        errorCode = GetLastError();
        CloseHandle(hDevice);
        exit(errorCode);
    }
}

HANDLE DeviceHandler::CreateHandle(WCHAR * volumeName)
{
    HANDLE diskHandle = CreateFileW(volumeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(diskHandle == INVALID_HANDLE_VALUE) {
        errorCode = GetLastError();
        CloseHandle(diskHandle);
        exit(errorCode);
    }
    return diskHandle;
}

BYTE * DeviceHandler::ReadFileSystem(HANDLE & hDevice, ULONGLONG & recordOffset, DWORD & bytesToRead)
{
    LARGE_INTEGER sectorOffset;
    sectorOffset.QuadPart = recordOffset;
    BYTE * recordBuffer = new BYTE[bytesToRead];
    currentOffset = SetFilePointer(hDevice, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
    if (currentOffset != sectorOffset.LowPart) {
        errorCode = GetLastError();
        CloseHandle(hDevice);
        exit(errorCode);
    }
    bool readResult = ReadFile(hDevice, recordBuffer, bytesToRead, &bytesReturned, NULL);
    if(!readResult || bytesReturned != bytesToRead) {
        errorCode = GetLastError();
        CloseHandle(hDevice);
        exit(errorCode);
    }
    return recordBuffer;
}

PFileSystem DeviceHandler::GetFileSystem(WCHAR *volumeName)
{
    hDevice = CreateHandle(volumeName);
    ULONGLONG bootRecordOffset = 0;
    GetDiskGeometry(diskGeometry, hDevice);
    BYTE * recordBuffer = ReadFileSystem(hDevice, bootRecordOffset, diskGeometry.BytesPerSector);
    CommonFileRecord * bootRecordBuffer = (CommonFileRecord *) recordBuffer;
    BYTE * OEM = bootRecordBuffer->OEM_ID;
    if (!(_mbscmp(OEM, (BYTE*) _NTFS))) {
        return PFileSystem(new NTFS(hDevice, recordBuffer));
    }
    else {
        if (!(_mbscmp(OEM, (BYTE *) _exFAT)))
            return PFileSystem(new exFAT(hDevice, recordBuffer));
    }
    hDevice = NULL;
}

DeviceHandler::~DeviceHandler()
{

}
