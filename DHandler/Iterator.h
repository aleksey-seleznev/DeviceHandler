#ifndef ITERATOR_H
#define ITERATOR_H
#include "FileSystem.h"

class Iterator
{
private:
	pFileSystem fileSystem;
	ULONGLONG clusterOffset;
	ULONGLONG currentOffset;
	ULONGLONG totalClusters;
public:
	Iterator(pFileSystem fileSystem);
	Iterator(FileSystem * fileSystemPointer);
	ULONGLONG First();
	ULONGLONG Next();
	bool IsDone();
	void SetRange(ULONGLONG offsetValue, ULONGLONG clustersToRead); // Optional
	void ResetRange();
	Buffer GetCurrent();
	~Iterator();
};

#endif
