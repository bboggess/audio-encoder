#ifndef __MIDTREAD_QUANTIZER_H
#define __MIDTREAD_QUANTIZER_H

#include "Quantizer.h"

class MidtreadQuantizer : public Quantizer {
public:
    AudioSample Quantize(double sample, unsigned bitDepth);
    double Dequantize(AudioSample code);
};

#endif
