#include "Iterator.h"

Iterator::Iterator(pFileSystem fileSystemPointer) : fileSystem(fileSystemPointer)
{
	clusterOffset = fileSystem->GetClusterOffset();
	currentOffset = clusterOffset;
	totalClusters = fileSystem->GetTotalClusters() + 1;
}

Iterator::Iterator(FileSystem * fileSystemPointer) : fileSystem(fileSystemPointer)
{
	clusterOffset = fileSystem->GetClusterOffset();
	currentOffset = clusterOffset;
	totalClusters = fileSystem->GetTotalClusters() + 1;
}

ULONGLONG Iterator::First()
{
	return clusterOffset;
}

ULONGLONG Iterator::Next()
{
	return ++currentOffset;
}

bool Iterator::IsDone()
{
	return currentOffset < totalClusters ? true : false;
}

void Iterator::SetRange(ULONGLONG offsetValue, ULONGLONG clustersToRead)
{
	currentOffset += offsetValue;
	totalClusters = currentOffset + clustersToRead;
}

void Iterator::ResetRange()
{
	currentOffset = clusterOffset;
	totalClusters = fileSystem->GetTotalClusters();
}

Buffer Iterator::GetCurrent()
{
	return fileSystem->ReadClusters(currentOffset, 1);
}

Iterator::~Iterator()
{

}