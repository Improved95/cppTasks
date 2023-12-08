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

    streamInObj.stream.read(reinterpret_cast<char*>(streamInObj.header), 4 + 4 + 4); // SIZE_OF_CHUNK_NAME + размер чанка + 'WAVE'

    /*try {
        if (!compareString(streamInObj.header->riff, "RIFF") || !compareString(streamInObj.header->format, "WAVE")) {
            throw FilesFormatExceptions(streamInObj.fileName);
        }
    } catch (FilesFormatExceptions &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }*/

    streamInObj.fileSize = streamInObj.header->chunkSize + 8;

    return 0;
}

int ParserFmt::parse(BinaryStreamIn &streamInObj) {


    return 0;
}

int ParserLIST::parse(BinaryStreamIn &streamInObj) {
    return 0;
}

int BinaryStreamIn::parseMetadataInWavFile(const size_t frequency, const size_t bitsPerSample,
                                           const size_t numberOfChannels, const size_t compressingCode) {
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
