#include "Streams.h"
#include "Exceptions.h"
#include <vector>
#include <cstring>
#include "functional"
using std::function;
using std::cerr;
using std::endl;
using std::vector;

int BinaryStreamIn::openFile(const string &fileName) {
    int r;
    this->stream.open(fileName, std::ios::in | std::ios::binary);
    r = checkFileOpen(fileName);
    return r;
}


int BinaryStreamOut::openFile(const string &fileName) {
    this->stream.open(fileName, std::ios::out | std::ios::binary);
    return checkFileOpen(fileName);
}

int StreamIn::openFile(const std::string &fileName) {
    this->stream.open(fileName, std::ios::in);
    return checkFileOpen(fileName);
}

int Stream::checkFileOpen(const string &fileName) {
    try {
        if (!this->stream.is_open()) {
            throw FileNotOpenException(fileName);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }
    return 0;
}

char * BinaryStreamIn::samplesInOneSecond = nullptr;
char *BinaryStreamIn::getSamplesInOneSecond(const size_t second, const size_t frequency,
                                            const size_t bitsPerSample) {

    this->stream.read(samplesInOneSecond, frequency * (bitsPerSample / BITS_PER_BYTE));

    return samplesInOneSecond;
}

int BinaryStreamIn::parseMetadataInWavFile(const size_t frequency, const size_t bitsPerSample,
                                           const size_t numberOfChannels, const size_t compressingCode) {
    /*эксепшоны в этом методе не работают, поэтому здесь не будет,
     * здесь вообще ничего не работает, если быть честным, strcmp тоже не работает*/
    this->metadataSize = 8;

    //RIFF
    char data[4];
    this->stream.read(data, 4);

    if (strcmp(data, "RIFF") != 0) { return 8; }

    //размер файла
    this->stream.read(data, 4);
    unsigned int fileSize =  *reinterpret_cast<int*>(data) + 8;

    //WAVE
    this->stream.read(data, 4);
    if (strcmp(data, "WAVE") != 0) { return 8; }

    //fmt
    this->stream.read(data, 4);
    if (strcmp(data, "fmt ") != 0) { return 8; }

    //размер данных блока fmt
    this->stream.read(data, 4);
    this->metadataSize += *reinterpret_cast<int*>(data);

    //код сжатия
    this->stream.read(data, 2);
    int dataInt = *reinterpret_cast<int*>(data);
    if (dataInt != compressingCode) { return 8; }

    //количество каналов
    this->stream.read(data, 2);
    dataInt = *reinterpret_cast<int*>(data);
    if (dataInt != compressingCode) { return 8; }

    //частота дискретизации
    this->stream.read(data, 4);
    dataInt = *reinterpret_cast<int*>(data);
    if (dataInt != frequency) { return 8; }

    //количество байт в секунде
    this->stream.read(data, 4);
    dataInt = *reinterpret_cast<int*>(data);
    if (dataInt != frequency * bitsPerSample / BITS_PER_BYTE) { return 8; }

    /*в первых двух байтах лежит некий размер блока, а во вторых двух
     * лежит количество значащих бит на выборку, чтобы это все не значило*/
    this->stream.read(data, 4);

    //list или data
    this->stream.read(data, 4);
    if (strcmp(data, "data") != 0 && strcmp(data, "LIST") != 0) { return 8; }

    this->stream.seekg(0, this->stream.beg);
    return 0;
}
