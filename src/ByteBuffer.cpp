#include "ByteBuffer.h"
#include <sstream>

ByteBuffer::ByteBuffer(size_t bufferSize)
    : size { bufferSize }
    , buffer { new char[size] }
{
}

ByteBuffer::ByteBuffer(const ByteBuffer& other)
    : size { other.size }
    , buffer { new char[size] }
{
    for (size_t i = 0; i < size; i++) {
        buffer[i] = other.buffer[i];
    }
}

ByteBuffer::ByteBuffer(ByteBuffer&& rhs)
    : size { rhs.size }
    , buffer { rhs.buffer }
{
    rhs.size = 0;
    rhs.buffer = nullptr;
}

ByteBuffer::~ByteBuffer()
{
    delete[] buffer;
}

// TODO: in constructor??
void ByteBuffer::ReadFromFile(std::ifstream& file)
{
    file.read(buffer, size);
}

size_t ByteBuffer::Size() const
{
    return size;
}

std::span<char> ByteBuffer::GetBytes(size_t start, size_t numBytes) const
{
    if (start + numBytes > size) {
        // TODO: refactor into own exception type
        std::stringstream msg;
        msg << "Cannot read bytes " << start << " to " << (start + numBytes - 1) << " in ByteBuffer of size " << size;
        throw std::out_of_range(msg.str());
    }

    return std::span<char> { buffer + start, numBytes };
}