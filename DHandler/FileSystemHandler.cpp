#include "FileSystemHandler.h"

FileSystemHandler::FileSystemHandler(pFileSystem fs) : fileSystem(fs) {}

NTFSHandler::NTFSHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer)
									: FileSystemHandler(pFileSystem(new NTFS(diskHandle, fileSystemBuffer))) {}

FATHandler::FATHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer)
									: FileSystemHandler(pFileSystem(new FAT(diskHandle, fileSystemBuffer))) {}

exFATHandler::exFATHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer)
									: FileSystemHandler(pFileSystem(new exFAT(diskHandle, fileSystemBuffer))) {}


Iterator FileSystemHandler::GetIterator()
{
	return Iterator(fileSystem);
}

void FileSystemHandler::FileSystemInfo()
{
	fileSystem->FileSystemInfo();
}

Buffer FileSystemHandler::ReadClusters(const ULONGLONG & startCluster, const DWORD & numberOfClusters)
{
	return fileSystem->ReadClusters(startCluster, numberOfClusters);
}

ULONGLONG FileSystemHandler::GetTotalClusters()
{
	return fileSystem->GetTotalClusters();
}

FileSystemHandler::~FileSystemHandler() {}

void NTFSHandler::CreateNewDirectory() {}

void NTFSHandler::CreateNewFile() {}

void FATHandler::CreateNewDirectory() {}

void FATHandler::CreateNewFile() {}

void exFATHandler::CreateNewDirectory() {}

void exFATHandler::CreateNewFile() {}