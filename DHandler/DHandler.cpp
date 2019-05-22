#include <iostream>
#include <windows.h>
#include <iomanip>
#include "DeviceHandler.h"

int main()
{
	std::cout << "System volumes information:" << std::endl;
	DeviceHandler deviceHandler;
	deviceHandler.GetSystemVolumes();
	DWORD clustersToRead, clusterOffset;
	WCHAR volumeName[8] = {NULL}, volumeCharacter;
	std::cout << "Specify volume character: ";
	std::wcin.get(volumeCharacter);
	std::cin.clear(); 
	std::cin.ignore(INT_MAX, '\n');
	deviceHandler.SetVolumeName(volumeName, volumeCharacter);
	pFileSystemHandler fileSystemHandler = deviceHandler.GetFileSystemHandler(volumeName);
	fileSystemHandler->FileSystemInfo();
	std::cout << "Enter cluster numbers to read: ";
	std::cin >> clustersToRead;
	std::cout << "Enter offset[0, " << fileSystemHandler->GetTotalClusters() << "]:";
	std::cin >> clusterOffset;
	Iterator clusterIterator = fileSystemHandler->GetIterator();
	clusterIterator.SetRange(clusterOffset, clustersToRead);
	for (clusterIterator.First(); clusterIterator.IsDone(); clusterIterator.Next())
	{
		FileSystem::PrintBuffer(clusterIterator.GetCurrent());
	}
	clusterIterator.ResetRange();
	system("pause");
}