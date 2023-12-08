#ifndef STREAMS
#define STREAMS

#include <iostream>
#include <fstream>
#include <vector>
#include "WavMetadataParse.h"
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::vector;
using std::string;

class Stream {
public:
    ~Stream() {
        this->stream.close();
    }

    fstream & getStream() { return this->stream; }

protected:
    fstream stream;
    virtual int openFile(const string &fileName) = 0;
    int checkFileOpen(const string &fileName);
};

struct WAVHeader {
    char subchunkRIFF[4]; //RIFF
    uint32_t fileSize; //размер файла минус 8
    char format[4]; //формат (WAVE)

    char subchunkFmt[4]; // название секции, должна быть fmt
    uint32_t subchunkFmtSize; //размер данных fmt
    uint16_t audioFormat; //формат аудиоданных
    uint16_t numberOfChannels; //кол-во аудиоканалов
    uint32_t sampleRate; //частота дискретизации
    uint32_t byteRate; //байтовая скорость
    uint16_t bytePerSample; //кол-во байтов для одного сэмпла
    uint16_t bitsPerSample; //кол-во битов для сэмпла

    char subchunkData[4]; //идентификатор второй подчасти
    uint32_t dataSize; //размер данных в этой подчасти
};

class BinaryStream : public Stream {
public:
    ~BinaryStream() {
        if (sampleBuffer != nullptr) {
            delete sampleBuffer;
        }
    }
    static void setSampleBuffer(const size_t bufferSize) {
        sampleBuffer = new char[bufferSize];
    }
    static char * getSampleBuffer() {
        return sampleBuffer;
    }
protected:
    static char *sampleBuffer;
};

class BinaryStreamIn : public BinaryStream, public CompareString {
public:
    BinaryStreamIn(const string &fileName_, int &r) {
        r = openFile(fileName_);
        this->fileName = fileName_;
    }
    ~BinaryStreamIn() {
        if (this->WAVheader != nullptr) {
            delete this->WAVheader;
        }
    }
    WAVHeader * getHeader() { return WAVheader; }

    char * getNewSamplesInOneSecond();
    char * getSamplesInOneSecond();
    int parseMetadataInWavFile(const size_t sampleRate, const size_t bytePerSample,
                                const size_t channels, const size_t audioFormat);

private:
    string fileName;
    WAVHeader *WAVheader;
    size_t metadataSize = 0;

    virtual int openFile(const string &fileName) override;

    friend ParserRIFF;
    friend ParserFmt;
    friend ParserLIST;
    friend ParserData;
};

class BinaryStreamOut : public Stream {
public:
    BinaryStreamOut(const string &fileName, int &r) {
        r = openFile(fileName);
    }
    ~BinaryStreamOut() {
        if (this->samplesBuffer != nullptr) {
            delete this->samplesBuffer;
        }
    }
    void setSamplesBuffer(char * samplesBuffer_) { samplesBuffer =  samplesBuffer_ ;}
    char * getSamplesBuffer() { return samplesBuffer; }

    void pushInFile(char *data, const size_t dataSize);

private:
    char *samplesBuffer = nullptr;

    virtual int openFile(const string &fileName) override;
};

class StreamIn : public Stream {
public:
    StreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

#endif
