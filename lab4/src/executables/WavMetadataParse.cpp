#include <iostream>
#include <functional>
#include "WavMetadataParse.h"
using std::function;

int ParserRIFF::parse(fstream &input, BinaryStreamIn &streamInObj) {
    input.seekg(0, input.beg);
//    input.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    return 0;
}

int ParserFmt::parse(fstream &input, BinaryStreamIn &streamInObj) {
    return 0;
}

int ParserLIST::parse(fstream &input, BinaryStreamIn &streamInObj) {
    return 0;
}

int BinaryStreamIn::parseMetadataInWavFile(const size_t frequency, const size_t bitsPerSample,
                                           const size_t numberOfChannels, const size_t compressingCode) {
    int r;
    WavMetadataParsersFactory parsersFactory;
    char data[4];

    this->stream.read(data, 4);
    WavMetadataParser *parser =  parsersFactory.create("RIFF");
    if ((r = parser->parse(this->stream, *this)) != 0) { return r; }

    do {
        //
    } while (data != "data");

    return 0;
}