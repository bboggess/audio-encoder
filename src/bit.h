#ifndef __BIT_H
#define __BIT_H

#include <cstdint>

/**
 * Take a two byte, little endian stream and package into an unsigned int.
 *
 * @param bytes An array with 2 bytes, least significant byte first. Does not verify proper formatting.
 */
constexpr uint16_t parseTwoBytes(const char bytes[])
{
    return ((uint8_t)bytes[1] << 8) | (uint8_t)bytes[0];
}

/**
 * Take a two byte, little endian stream and package into an unsigned int.
 *
 * @param bytes An array with 4 bytes, least significant byte first. Does not verify proper formatting.
 */
constexpr uint32_t parseFourBytes(const char bytes[])
{
    return ((uint8_t)bytes[3] << 24) | ((uint8_t)bytes[2] << 16) | ((uint8_t)bytes[1] << 8) | (uint8_t)bytes[0];
}

/**
 * Parses a two byte, little endian 2's complement signed byte stream.
 *
 * @param bytes An array with 2 bytes, least significant byte first. Does not verify this parameter.
 */
constexpr int16_t parseTwoSignedBytes(const char bytes[])
{
    return static_cast<int16_t>(parseTwoBytes(bytes));
}

/**
 * Parses a four byte, little endian 2's complement signed byte stream.
 *
 * @param bytes An array with 4 bytes, least significant byte first. Does not verify this parameter.
 */
constexpr int32_t parseFourSignedBytes(const char bytes[])
{
    return static_cast<int32_t>(parseFourBytes(bytes));
}

#endif