// DHandler.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <windows.h>
#include <memory>
#include "DeviceHandler.h"

int main()
{
	std::cout << "System volumes information:" << std::endl;
	DeviceHandler dHandler;
	dHandler.GetSystemVolumes();
	DWORD clustersToRead, clusterOffset;
	WCHAR volumeName[8] = {NULL}, volumeCharacter;
	std::cout << "Specify volume character: ";
	std::wcin.get(volumeCharacter);
	std::cin.clear(); 
	std::cin.ignore(INT_MAX, '\n');
	dHandler.SetVolumeName(volumeName, volumeCharacter);
	PFileSystem fileSystem = dHandler.GetFileSystem(volumeName);
	fileSystem->FileSystemInfo();
	std::cout << "Enter cluster numbers to read: ";
	std::cin >> clustersToRead;
	std::cout << "Enter offset[0, " << fileSystem.get()->GetTotalClusters() << "]:";
	std::cin >> clusterOffset;
	BUFFER clusterBuffer(fileSystem->ReadClusters(clusterOffset, clustersToRead));
	std::size_t bufferSize = fileSystem->GetBytesPerCluster() * clustersToRead;
	BYTE * bufferIterator = clusterBuffer.get();
	for (DWORD count = 0; count < bufferSize; count++)
	{
		std::cout << std::hex << DWORD(*bufferIterator) << " ";
		bufferIterator++;
	}
	system("pause");
	return 0;
}