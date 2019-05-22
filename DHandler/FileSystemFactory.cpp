#include "FileSystemFactory.h"

enum FileSystemName {
	FAT_Name,
	NTFS_Name,
	exFAT_Name
};

FileSystemName DetectFileSystem(const std::string & fileSystemName)
{
	if (!fileSystemName.compare("MSDOS5.0")) return FAT_Name;
	if (!fileSystemName.compare("NTFS    ")) return NTFS_Name;
	if (!fileSystemName.compare("EXFAT   ")) return exFAT_Name;
}

FileSystemFactory::FileSystemFactory()
{

}


FileSystemHandler * FileSystemFactory::CreateFileSystemHandler(const HANDLE & hDevice, Buffer fileSystemBuffer)
{
	pFileSystemRecord bootRecordBuffer = (pFileSystemRecord) fileSystemBuffer.GetBuffer();
	BYTE * OEM = bootRecordBuffer->OEM_ID;
	std::string OEM_Name(reinterpret_cast<const char *>(OEM), sizeof(bootRecordBuffer->OEM_ID));
	switch (DetectFileSystem(OEM_Name)) {
		case FAT_Name:
			return new FATHandler(hDevice, fileSystemBuffer);
		case NTFS_Name:
			return new NTFSHandler(hDevice, fileSystemBuffer);
		case exFAT_Name:
			return new exFATHandler(hDevice, fileSystemBuffer);
		default:
				return NULL;
	}
}


FileSystemFactory::~FileSystemFactory()
{

}