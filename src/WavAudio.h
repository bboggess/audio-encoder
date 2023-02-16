#ifndef __WAVE_AUDIO_H
#define __WAVE_AUDIO_H

#include "QuantizedAudio.h"
#include <fstream>

class WaveAudio : public QuantizedAudio {
public:
    WaveAudio(std::ifstream& file);

    unsigned NumChannels() const;
    unsigned SamplesPerSecond() const;
    unsigned BitDepth() const;

    AudioChannel Channel(int channelNumber) const;

private:
    unsigned numChannels;
    unsigned samplesPerSecond;
    unsigned bitDepth;

    std::vector<std::vector<AudioSample>> samples;
};

#endif
