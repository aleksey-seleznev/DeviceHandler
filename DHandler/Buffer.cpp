#include "Buffer.h"

Buffer::Buffer() : fileSystemBuffer(NULL)
{
	bufferSize = 0;
}

Buffer::Buffer(pBuffer buffer, std::size_t size) : fileSystemBuffer(buffer)
{
	bufferSize = size;
}

Buffer::Buffer(BYTE * buffer, std::size_t size) : fileSystemBuffer(buffer)
{
	bufferSize = size;
}

BYTE * Buffer::GetBuffer()
{
	return fileSystemBuffer.get();
}

const std::size_t & Buffer::GetBufferSize()
{
	return bufferSize;
}

Buffer & Buffer::operator=(Buffer buffer)
{
	fileSystemBuffer = pBuffer(buffer.GetBuffer());
	bufferSize = buffer.GetBufferSize();
	return *this;
}
