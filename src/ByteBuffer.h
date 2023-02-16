#ifndef __WAVE_BYTE_BUFFER_H
#define __WAVE_BYTE_BUFFER_H

#include <cstdint>
#include <fstream>
#include <span>

/**
 * Holds a stream of bytes.
 */
class ByteBuffer {
public:
    /**
     * Creates empty byte buffer
     * @param bufferSize The number of bytes the buffer will hold
     */
    ByteBuffer(size_t bufferSize);
    ByteBuffer(const ByteBuffer&);
    ByteBuffer(ByteBuffer&&);
    ~ByteBuffer();

    // overwrites data if called multiple times
    /**
     * Fill the buffer with data from a file. It is assumed
     * that you want to fill the entire buffer, so make sure not to read
     * past the end of the file.
     *
     * @param file A binary file to read from, starting from current position
     */
    void ReadFromFile(std::ifstream& file);

    /**
     * The number of btyes the buffer holds
     */
    size_t Size() const;

    /**
     * Gets a sequence of bytes, starting from any point in the buffer. Throws
     * out_of_range if reading numBytes goes past the end of the buffer.
     *
     * @param start Index of first byte to read
     * @param numBytes The number of bytes to return
     * @return Exactly numBytes bytes from the buffer
     */
    // TODO: generalize argument type to not repeat
    std::span<char> GetBytes(size_t start, size_t numBytes) const;

private:
    // the amount of space we've allocated
    size_t size;
    char* buffer;
};

#endif
