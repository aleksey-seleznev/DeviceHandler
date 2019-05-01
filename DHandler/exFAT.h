//
// Created by aseleznev on 24.04.2019.
//
#ifndef EXFAT_H
#define EXFAT_H
#include <cmath>
#include "FileSystem.h"
#define _exFAT "EXFAT   "

typedef struct
{
    BYTE Padding1[3];
    BYTE OEM_Name[8];
    BYTE Padding2[61];
    ULONGLONG TotalSectors; // Количество секторов в файловой системе
    DWORD FATStartSector; // Сектор в котором начинается exFAT
    DWORD FATSizeInSectors; // Размер exFAT в секторах
    DWORD FirstDataSector; // Сектор в котором начинается битовая карта кластеров
    DWORD TotalClusters; // Количество кластеро в файловой системе
    DWORD RootDirCluster; // Кластер, в котором находится корневой каталог
    BYTE Padding3[8];
    BYTE SectorFactor; // Степень размера сектора в байтах
    BYTE ClusterFactor; // Степень размера кластера в байтах
} exFAT_BootRecord;

class exFAT: public FileSystem
{
public:
    exFAT(const HANDLE & hDevice, BYTE * bootRecordBuffer);
    virtual BUFFER FSReadFile();
    ~exFAT();
};

/*
Not used
#undef max
template <class T>
T ReverseWord(T sourceWord)
{
	T reversedWord = 0;
	std::size_t wordSize = sizeof(T);
	T leftLimit = std::numeric_limits<T>::max(T) >> 1;
	leftLimit++;
	T rightLimit = leftLimit >> (wordSize - 1) * BYTE_SIZE;
	for (unsigned bytes = 0; bytes < wordSize; bytes++) {
		for (unsigned bits = 0; bits < BYTE_SIZE; bits++) {
			if (sourceWord & (rightLimit >> bits))
				reversedWord |= (leftLimit >> (bytes * BYTE_SIZE + bits));
		}
		rightLimit <<= BYTE_SIZE;
	};
	return reversedWord;
}
*/

#endif //EXFAT_H
