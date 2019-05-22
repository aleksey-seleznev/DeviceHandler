#ifndef FILESYSTEMHANDLER_H
#define FILESYSTEMHANDLER_H
#include "Iterator.h"
#include "NTFS.h"
#include "FAT.h"
#include "exFAT.h"

class FileSystemHandler
{
protected:
	pFileSystem fileSystem;
public:
	FileSystemHandler(pFileSystem fs);
	Iterator GetIterator();
	void FileSystemInfo();
	Buffer ReadClusters(const ULONGLONG & startCluster, const DWORD & numberOfClusters);
	ULONGLONG GetTotalClusters();
	virtual void CreateNewDirectory() = 0;
	virtual void CreateNewFile() = 0;
	~FileSystemHandler();
};

class NTFSHandler : public FileSystemHandler
{
public:
	NTFSHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer);
	virtual void CreateNewDirectory();
	virtual void CreateNewFile();
};

class FATHandler : public FileSystemHandler
{
public:
	FATHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer);
	virtual void CreateNewDirectory();
	virtual void CreateNewFile();
};

class exFATHandler : public FileSystemHandler
{
public:
	exFATHandler(const HANDLE & diskHandle, Buffer fileSystemBuffer);
	virtual void CreateNewDirectory();
	virtual void CreateNewFile();
};

typedef std::shared_ptr<FileSystemHandler> pFileSystemHandler;
#endif

