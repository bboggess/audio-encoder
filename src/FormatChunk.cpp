#include "FormatChunk.h"
#include "bit.h"
#include <exception>

// The WAVE format requires the format chunk to be at least 16 bytes
constexpr unsigned MinBytesInChunk = 16;

FormatChunk::FormatChunk(const char data[], unsigned size)
{
    if (size < MinBytesInChunk) {
        throw std::exception();
    }

    unsigned offset = 0;

    formatTag = parseTwoBytes(data + offset);
    offset += sizeof(formatTag);

    numChannels = parseTwoBytes(data + offset);
    offset += sizeof(numChannels);

    samplesPerSecond = parseFourBytes(data + offset);
    offset += sizeof(samplesPerSecond);

    avgBytesPerSecond = parseFourBytes(data + offset);
    offset += sizeof(avgBytesPerSecond);

    blockSize = parseTwoBytes(data + offset);
    offset += sizeof(blockSize);

    bitsPerSample = parseTwoBytes(data + offset);
    offset += sizeof(bitsPerSample);
}