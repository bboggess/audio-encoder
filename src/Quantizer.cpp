#include "Quantizer.h"
#include "MidriseQuantizer.h"
#include "MidtreadQuantizer.h"

AudioQuantizer::AudioQuantizer(QuantizationType type, unsigned bitDepth)
{
    if (bitDepth < 0 || bitDepth > 32) {
        throw std::exception();
    }

    this->bitDepth = bitDepth;

    switch (type) {
    case QuantizationType::Midrise:
        quantizer = std::make_unique<MidriseQuantizer>();
        break;

    case QuantizationType::Midtread:
        quantizer = std::make_unique<MidtreadQuantizer>();
        break;
    }
}

AudioSample AudioQuantizer::Quantize(double sample) const
{
    return quantizer->Quantize(sample, bitDepth);
}

double AudioQuantizer::Dequantize(AudioSample code) const
{
    return quantizer->Dequantize(code);
}