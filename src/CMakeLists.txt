set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES WavAudio.cpp FormatChunk.cpp DataChunk.cpp ByteBuffer.cpp MidriseQuantizer.cpp MidtreadQuantizer.cpp Quantizer.cpp SampledAudio.cpp)
set(BIN_SOURCES ${SOURCES} main.cpp)

add_executable(${BINARY} ${BIN_SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})