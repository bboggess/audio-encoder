#ifndef __QUANTIZED_AUDIO_H
#define __QUANTIZED_AUDIO_H

#include <variant>
#include <vector>

typedef std::variant<char, int16_t, int32_t> AudioSample;

class QuantizedAudio {
public:
    typedef std::vector<AudioSample> AudioChannel;

    virtual unsigned NumChannels() const = 0;
    virtual unsigned SamplesPerSecond() const = 0;
    virtual unsigned BitDepth() const = 0;
    virtual AudioChannel Channel(int channelNumber) const = 0;
};

#endif
