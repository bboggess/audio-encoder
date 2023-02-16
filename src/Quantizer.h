#ifndef __QUANTIZER_H
#define __QUANTIZER_H

#include "QuantizedAudio.h"
#include <memory>

class Quantizer {
public:
    virtual AudioSample Quantize(double sample, unsigned bitDepth) = 0;
    virtual double Dequantize(AudioSample code) = 0;
};

// no template -- we don't know at compile time what size we need
class AudioQuantizer {
public:
    enum class QuantizationType {
        Midrise,
        Midtread
    };

    AudioQuantizer(QuantizationType type, unsigned bitDepth);
    AudioSample Quantize(double sample) const;
    double Dequantize(AudioSample code) const;

private:
    std::unique_ptr<Quantizer> quantizer;
    unsigned bitDepth;
};

#endif
