#ifndef __DATA_CHUNK_H
#define __DATA_CHUNK_H

#include "ByteBuffer.h"
#include "FormatChunk.h"
#include <variant>
#include <vector>

/**
 * Audio samples are stored in different formats depending on the file's bit
 * depth. This type abstracts away that difference.
 */
typedef std::variant<char, int16_t, int32_t> AudioSample;

/**
 * Parses the data chunk from a WAVE file.
 */
class DataChunk {
public:
    /**
     * Represents a stream of samples in a single channel
     */
    typedef std::vector<AudioSample> AudioChannel;

    /**
     * Parses data bytes into properly formatted channel data.
     *
     * @param data a buffer containing all the data we need
     * @param formatChunk Format chunk of the WAVE file, containing sample metadata
     */
    DataChunk(ByteBuffer data, FormatChunk formatChunk);

    /**
     * All audio samples, split up by channel
     */
    std::vector<AudioChannel> samples;
};

#endif
