#include "MidriseQuantizer.h"
#include <gtest/gtest.h>

class MidriseQuantizerTest : public ::testing::Test {
protected:
    MidriseQuantizer quantizer;
};

TEST_F(MidriseQuantizerTest, ClipsTooLarge)
{
    int16_t expected = (1 << 15) - 1;
    int16_t result = std::get<int16_t>(quantizer.Quantize(2.0, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, ClipsTooSmall)
{
    int16_t expected = -((1 << 15) - 1);
    int16_t result = std::get<int16_t>(quantizer.Quantize(-2.0, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, SmallPositiveAmplitude)
{
    int16_t expected = 0;
    double amplitude = 1.0 / (1 << 17);
    int16_t result = std::get<int16_t>(quantizer.Quantize(amplitude, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, SmallNegativeAmplitude)
{
    int16_t expected = 0;
    double amplitude = -1.0 / (1 << 17);
    int16_t result = std::get<int16_t>(quantizer.Quantize(amplitude, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, AmplitudeOneHalf)
{
    int16_t expected = 1 << 14;
    int16_t result = std::get<int16_t>(quantizer.Quantize(0.5, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, LargeNegativeAmplitude)
{
    int16_t expected = -0x2CF4;
    double amplitude = -0.3512;
    int16_t result = std::get<int16_t>(quantizer.Quantize(amplitude, 16));
    EXPECT_EQ(result, expected);
}

TEST_F(MidriseQuantizerTest, MaxQuantizedCode)
{
    int16_t code = (1 << 15) - 1;
    double expected = 0.9999847412109375;
    EXPECT_DOUBLE_EQ(quantizer.Dequantize(code), expected);
}

TEST_F(MidriseQuantizerTest, MinQuantizedCode)
{
    int16_t code = -((1 << 15) - 1);
    double expected = -0.9999847412109375;
    EXPECT_DOUBLE_EQ(quantizer.Dequantize(code), expected);
}

TEST_F(MidriseQuantizerTest, LargePositiveCode)
{
    int16_t code = 0x000F;
    double expected = 0.0004730224609375;
    EXPECT_DOUBLE_EQ(quantizer.Dequantize(code), expected);
}