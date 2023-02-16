#include "SampledAudio.h"
#include "QuantizedAudio.h"
#include "Quantizer.h"
#include <algorithm>
#include <vector>

SampledAudio::SampledAudio(const QuantizedAudio* file, const AudioQuantizer& quantizer)
    : numChannels { file->NumChannels() }
    , samplesPerSecond { file->SamplesPerSecond() }
    , samples { numChannels }
{
    // TODO: this can be parallelized, right?
    for (size_t channelNum = 0; channelNum < numChannels; channelNum++) {
        const auto quantizedChannel = file->Channel(channelNum);
        samples[channelNum].resize(quantizedChannel.size());

        std::transform(quantizedChannel.begin(),
            quantizedChannel.end(),
            samples[channelNum].begin(),
            [&quantizer](const AudioSample& sample) -> double { return quantizer.Dequantize(sample); });
    }
}

std::vector<double> SampledAudio::Channel(int i) const
{
    return samples[i];
}