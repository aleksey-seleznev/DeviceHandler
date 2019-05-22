#ifndef BUFFER_H
#define BUFFER_H
#include <memory>
#include <windows.h>
typedef std::shared_ptr<BYTE> pBuffer;

class Buffer
{
private:
	pBuffer fileSystemBuffer;
	std::size_t bufferSize;
public:
	Buffer();
	Buffer(pBuffer fileSystemBuffer, std::size_t bufferSize);
	Buffer(BYTE * fileSystemBuffer, std::size_t bufferSize);
	BYTE *  GetBuffer();
	const std::size_t & GetBufferSize();
	Buffer & operator=(Buffer fileSystemBuffer);
};

#endif
