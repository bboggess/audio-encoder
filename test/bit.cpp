#include "bit.h"
#include <gtest/gtest.h>

TEST(BitTest, LittleEndianHighBit)
{
    uint16_t expected = 0xFF00;
    char bytes[] { 0, static_cast<char>(0xFF) };
    EXPECT_EQ(parseTwoBytes(bytes), expected);
}

TEST(BitTest, LittleEndianLowBit)
{
    uint16_t expected = 0X000F;
    char bytes[] { 15, 0 };
    EXPECT_EQ(parseTwoBytes(bytes), expected);
}

TEST(BitTest, TwosComplementHandlesNegativeInteger)
{
    int16_t expected = -32768;
    char bytes[] { 0, static_cast<char>(1 << 7) };
    EXPECT_EQ(parseTwoSignedBytes(bytes), expected);
}

TEST(BitTest, TwosComplementHandlesPositiveInteger)
{
    int16_t expected = 0x0F;
    char bytes[] { 15, 0 };
    EXPECT_EQ(parseTwoSignedBytes(bytes), expected);
}