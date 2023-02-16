#include "DataChunk.h"
#include "FormatChunk.h"
#include "bit.h"
#include <exception>
#include <span>

/**
 * @param bytes An array of bytes, starting from first address and reading numBytes bytes
 * @param numBytes The number of bytes to parse from the buffer. Assuemd to be at least 1, at most 4
 */
AudioSample parseSample(std::span<char> bytes)
{
    if (bytes.size() == 1) {
        return bytes[0];
    } else if (bytes.size() == 2) {
        return parseTwoSignedBytes(bytes.data());
    } else {
        return parseFourSignedBytes(bytes.data());
    }
}

DataChunk::DataChunk(ByteBuffer data, FormatChunk formatChunk)
{
    const uint16_t numChannels = formatChunk.numChannels;
    const size_t bytesPerSample = formatChunk.bitsPerSample / 8;
    const unsigned numSamples = data.Size() / bytesPerSample;
    unsigned samplesPerChannel = numSamples / bytesPerSample / numChannels;

    if (bytesPerSample < 1 || bytesPerSample > 4) {
        throw std::exception();
    }

    // we know exactly how much storage we need, so go ahead and reserve it
    samples.resize(numChannels);
    for (AudioChannel channel : samples) {
        channel.reserve(samplesPerChannel);
    }

    size_t channelNum = 0;
    for (size_t sampleNumber = 0; sampleNumber < numSamples; sampleNumber++) {
        const size_t startingByte = sampleNumber * bytesPerSample;
        samples[channelNum].push_back(parseSample(data.GetBytes(startingByte, bytesPerSample)));
        channelNum = (channelNum + 1) % numChannels;
    }
}