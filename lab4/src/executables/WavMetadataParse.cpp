#include <iostream>
#include <functional>
#include <Streams.h>
#include "WavMetadataParse.h"
#include "Exceptions.h"

using std::function;
using std::cerr;
using std::endl;

bool CompareString::compareString(const string &s1, const string &s2) {
    for (size_t i = 0; i < s2.size(); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

int ParserRIFF::parse(BinaryStreamIn &streamInObj) {
    streamInObj.stream.seekg(0, streamInObj.stream.beg);
    streamInObj.header = new WAVHeader;

    streamInObj.stream.read(reinterpret_cast<char*>(streamInObj.header), 12); // SIZE_OF_CHUNK_NAME + размер чанка + 'WAVE'

    /*try {
        if (!compareString(streamInObj.header->riff, "RIFF") || !compareString(streamInObj.header->format, "WAVE")) {
            throw FilesFormatExceptions(streamInObj.fileName);
        }
    } catch (FilesFormatExceptions &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }*/

    streamInObj.header->metadataSize += 12;

    return 0;
}

int ParserFmt::parse(BinaryStreamIn &streamInObj) {
    streamInObj.stream.seekg(-4, streamInObj.stream.cur);

    streamInObj.stream.read(reinterpret_cast<char*>(streamInObj.header) + 12, 24);

    if (streamInObj.header->frequency != streamInObj.WAVparameters->frequency ||
            streamInObj.header->bytePerSample != streamInObj.WAVparameters->bytePerSample ||
            streamInObj.header->numberOfChannels != streamInObj.WAVparameters->numberOfChannels ||
            streamInObj.header->audioFormat != streamInObj.WAVparameters->audioFormat) {
        return 6;
    }

    streamInObj.header->metadataSize += 24;

    return 0;
}

int ParserLIST::parse(BinaryStreamIn &streamInObj) {
    char intData[4];
    streamInObj.stream.read(intData, 4);

    size_t sizeOfListChunk = *reinterpret_cast<int*>(intData);
    streamInObj.header->metadataSize += 8 + sizeOfListChunk;
    streamInObj.stream.seekg(sizeOfListChunk, streamInObj.stream.cur);

    return 0;
}

int ParserData::parse(BinaryStreamIn &streamInObj) {
    streamInObj.stream.seekg(-4, streamInObj.stream.cur);

    streamInObj.stream.read(reinterpret_cast<char*>(streamInObj.header) + 36, 8);
    if (!compareString(streamInObj.header->subchunkData, "data")) {
        return 6;
    }

    streamInObj.header->metadataSize += 8;

    return 0;
}

int BinaryStreamIn::parseMetadataInWavFile() {
    int r;
    WavMetadataParsersFactory parsersFactory;
    char data[SIZE_OF_CHUNK_NAME + 1];
    data[4] = '\0';

    this->stream.read(data, SIZE_OF_CHUNK_NAME);
    WavMetadataParser *parser =  parsersFactory.create("RIFF");
    if ((r = parser->parse(*this)) != 0) { return r; }

    do {
        this->stream.read(data, SIZE_OF_CHUNK_NAME);
        WavMetadataParser *parser =  parsersFactory.create(data);
        if (parser == nullptr) { return 6; }

        if ((r = parser->parse(*this)) != 0) { return r; }
    } while (!compareString(data, "data"));

    return 0;
}
