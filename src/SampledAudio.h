#ifndef __SAMPLED_AUDIO_H
#define __SAMPLED_AUDIO_H

#include "QuantizedAudio.h"
#include "Quantizer.h"
#include <vector>

class SampledAudio {
public:
    SampledAudio(const QuantizedAudio* wave, const AudioQuantizer& quantizer);
    unsigned NumChannels() const;
    unsigned SamplesPerSecond() const;

    std::vector<double> Channel(int i) const;

private:
    unsigned numChannels;
    unsigned samplesPerSecond;
    // TODO: no
    std::vector<std::vector<double>> samples;
};

#endif
