#include "MidriseQuantizer.h"
#include <cmath>
#include <concepts>

template <std::signed_integral T>
T absoluteValue(T x)
{
    return x >= 0 ? x : -x;
}

template <typename T>
requires std::floating_point<T> || std::signed_integral<T>
int sign(T x)
{
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}

template <std::signed_integral T>
constexpr T maxCodeValue = std::numeric_limits<T>::max();

template <std::signed_integral T>
T quantize(double sample)
{
    T quantized;
    const double absValue = fabs(sample);

    if (absValue >= 1) {
        quantized = maxCodeValue<T>;
    } else {
        quantized = static_cast<T>(absValue * (1 << 15));
    }

    return sign<double>(sample) * quantized;
}

template <std::signed_integral T>
double dequantize(T quantized)
{
    const double absValue = (absoluteValue(quantized) + 0.5) / (1 << 15);
    return sign<T>(quantized) * absValue;
}

AudioSample MidriseQuantizer::Quantize(double sample, unsigned bitDepth)
{
    switch (bitDepth / 8) {
    case 2:
        return quantize<int16_t>(sample);
        break;

    case 4:
        return quantize<int32_t>(sample);
        break;

    default:
        throw std::exception();
        break;
    }
}

double MidriseQuantizer::Dequantize(AudioSample code)
{
    if (std::holds_alternative<int16_t>(code)) {
        return dequantize<int16_t>(std::get<int16_t>(code));
    } else if (std::holds_alternative<int32_t>(code)) {
        return dequantize<int32_t>(std::get<int32_t>(code));
    } else {
        throw std::exception();
    }
}