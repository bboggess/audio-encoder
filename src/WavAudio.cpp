#include "WavAudio.h"
#include "ByteBuffer.h"
#include "DataChunk.h"
#include "FormatChunk.h"
#include "bit.h"
#include <fstream>
#include <string_view>

typedef uint32_t ChunkID;
typedef uint32_t ChunkSize;

struct ChunkHeader {
    ChunkID id;
    ChunkSize size;
};

using namespace std::string_view_literals;

/**
 * Pack the human readable chunk ID into something that fits better into our
 * data struct. Build known chunk IDs by passing strings into this.
 *
 * @param id human readable ID string, e.g. "RIFF"
 * @returns chunk ID put in format that will be packed into struct read from file
 */
constexpr ChunkID idStringToChunkId(std::string_view idString)
{
    return parseFourBytes(idString.data());
}

/*
 * ID strings used in WAVE chunk headers.
 */
constexpr std::string_view RiffIdString = "RIFF"sv;
constexpr std::string_view WaveIdString = "WAVE"sv;
constexpr std::string_view FmtIdString = "fmt "sv;
constexpr std::string_view DataIdString = "data"sv;
/**
 * IDs in the format they will be read from the file.
 */
constexpr ChunkID RiffId = idStringToChunkId(RiffIdString);
constexpr ChunkID WavId = idStringToChunkId(WaveIdString);
constexpr ChunkID FmtId = idStringToChunkId(FmtIdString);
constexpr ChunkID DataId = idStringToChunkId(DataIdString);

/**
 * Reads a two byte piece of data from a little endian formatted file
 *
 * @param file File to read from. Will read from current location.
 * @returns the next two bytes of data
 */
uint16_t readTwoBytesFromFile(std::ifstream& file)
{
    char data[2];
    file.read(data, sizeof(data));
    return parseTwoBytes(data);
}

/**
 * Reads a four byte piece of data from a little endian formatted file.
 *
 * @param file File to read from. Will read from current location.
 * @returns the next four bytes of data
 */
uint32_t readFourBytesFromFile(std::ifstream& file)
{
    char data[4];
    file.read(data, sizeof(data));
    return parseFourBytes(data);
}

/**
 * Reads a chunk header from the current position in a WAV file.
 *
 * @param file The file, set to the position you want to read from
 * @returns Chunk header at the current file position
 */
ChunkHeader readChunkHeader(std::ifstream& file)
{
    const ChunkID chunkId = readFourBytesFromFile(file);
    const ChunkSize chunkSize = readFourBytesFromFile(file);

    return ChunkHeader { chunkId, chunkSize };
}

void skipChunk(std::ifstream& file, ChunkHeader header)
{
    file.seekg(header.size);
}

FormatChunk parseFormatChunk(std::ifstream& file, ChunkHeader header)
{
    const ChunkSize chunkSize = header.size;
    char buffer[chunkSize];
    file.read(buffer, chunkSize);
    return FormatChunk(buffer, chunkSize);
}

DataChunk parseDataChunk(std::ifstream& file, ChunkHeader header, FormatChunk formatChunk)
{
    const ChunkSize dataSize = header.size;
    ByteBuffer buffer(dataSize);
    buffer.ReadFromFile(file);
    DataChunk data(buffer, formatChunk);

    // read placeholder byte if there is one
    if (header.size % 2 != 0) {
        file.seekg(1);
    }

    return data;
}

/**
 *
 * @returns the number of bytes in the file, not counting the RIFF header or WAV ID
 */
ChunkSize verifyFileHeader(std::ifstream& file)
{
    const ChunkHeader riffHeader = readChunkHeader(file);
    if (riffHeader.id != RiffId) {
        throw std::exception();
    }

    const ChunkID wavID = readFourBytesFromFile(file);
    if (wavID != WavId) {
        throw std::exception();
    }

    return riffHeader.size - sizeof(wavID);
}

ChunkHeader findChunkHeader(std::ifstream& file, ChunkID toFind, ChunkSize bytesLeft)
{
    ChunkSize numBytesRead = 0;
    ChunkHeader nextHeader;
    bool found = false;

    while (numBytesRead < bytesLeft) {
        nextHeader = readChunkHeader(file);
        if (nextHeader.id == toFind) {
            found = true;
            break;
        } else {
            // ignore all optional or unknown chunks
            skipChunk(file, nextHeader);
        }

        numBytesRead += nextHeader.size + sizeof(ChunkID);
    }

    if (!found) {
        throw std::exception();
    }

    return nextHeader;
}

struct WaveFile {
    FormatChunk formatChunk;
    DataChunk dataChunk;
};

WaveFile readFile(std::ifstream& file)
{
    const ChunkSize totalNumBytes = verifyFileHeader(file);
    ChunkSize numBytesRead = 0;

    const ChunkHeader formatHeader = readChunkHeader(file);
    if (formatHeader.id != FmtId) {
        throw std::exception();
    }
    const FormatChunk formatChunk = parseFormatChunk(file, formatHeader);
    numBytesRead += formatHeader.size + sizeof(formatHeader);

    const ChunkHeader dataChunkHeader = findChunkHeader(file, DataId, totalNumBytes - numBytesRead);
    const DataChunk dataChunk = parseDataChunk(file, dataChunkHeader, formatChunk);

    return WaveFile { formatChunk, dataChunk };
}

WaveAudio::WaveAudio(std::ifstream& file)
{
    WaveFile waveFile = readFile(file);

    numChannels = waveFile.formatChunk.numChannels;
    samplesPerSecond = waveFile.formatChunk.samplesPerSecond;
    bitDepth = waveFile.formatChunk.bitsPerSample;
    samples = waveFile.dataChunk.samples;
}

QuantizedAudio::AudioChannel WaveAudio::Channel(int channelNumber) const
{
    return samples[channelNumber];
}

unsigned WaveAudio::NumChannels() const
{
    return numChannels;
}
unsigned WaveAudio::SamplesPerSecond() const
{
    return samplesPerSecond;
}

unsigned WaveAudio::BitDepth() const
{
    return bitDepth;
}