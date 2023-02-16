#include "QuantizedAudio.h"
#include "Quantizer.h"
#include "SampledAudio.h"
#include "WavAudio.h"
#include <fstream>
#include <iostream>
#include <memory>

// For now, basically a test driver for the WAV quantization.
// Eventually, this will read a WAV and write to a different format.
int main(int argc, char** argv)
{
    std::ifstream inFile(argv[1], std::ios::binary | std::ios::in);
    std::unique_ptr<QuantizedAudio> wave = std::make_unique<WaveAudio>(inFile);

    std::cout << "num channels: " << wave->NumChannels() << std::endl;
    std::cout << "samples per sec: " << wave->SamplesPerSecond() << std::endl;
    std::cout << "bits per sample: " << wave->BitDepth() << std::endl;

    auto sampled = std::make_unique<SampledAudio>(wave.get(), AudioQuantizer { AudioQuantizer::QuantizationType::Midrise, 16 });
}
