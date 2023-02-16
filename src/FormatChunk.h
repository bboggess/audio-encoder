#ifndef __FORMAT_CHUNK_H
#define __FORMAT_CHUNK_H

#include <cstdint>

/**
 * Parses the format chunk from a WAVE file.
 */
class FormatChunk {
public:
    /**
     * Parses the body of the format chunk into recognizable fields.
     *
     * @param data Body of the format chunk, represented as bytes in the same order.
     * @param size The number of bytes in the chunk body
     */
    FormatChunk(const char data[], unsigned size);

    uint16_t formatTag;
    uint16_t numChannels;
    uint32_t samplesPerSecond;
    uint32_t avgBytesPerSecond;
    uint16_t blockSize;
    uint16_t bitsPerSample;
};

#endif