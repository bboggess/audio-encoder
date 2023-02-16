#ifndef __MIDRISE_QUANTIZER_H
#define __MIDRISE_QUANTIZER_H

#include "Quantizer.h"

class MidriseQuantizer : public Quantizer {
public:
    AudioSample Quantize(double sample, unsigned bitDepth);
    double Dequantize(AudioSample code);
};

#endif
