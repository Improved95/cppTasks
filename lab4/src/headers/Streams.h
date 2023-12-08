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
#define BITS_PER_BYTE 8

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

struct WAVNeedsParameters {
    size_t sampleRate;
    size_t bytePerSample;
    size_t numberOfChannels;
    size_t audioFormat;
};

class BinaryStreamIn : public Stream, public CompareString {
public:
    BinaryStreamIn(const string &fileName_, const size_t sampleRate_, const size_t bytePerSample_,
    const size_t channels_, const size_t audioFormat_, int &r) {
        r = openFile(fileName_);
//        this->WAVparameters = new WAVNeedsParameters;
//        this->WAVparameters->sampleRate = sampleRate_;
//        this->WAVparameters->bytePerSample = bytePerSample_;
//        this->WAVparameters->numberOfChannels = channels_;
//        this->WAVparameters->audioFormat = audioFormat_;
        this->fileName = fileName_;
        if (this->samplesInOneSecond == nullptr) {
            this->samplesInOneSecond = new char[this->WAVparameters->sampleRate * this->WAVparameters->bytePerSample];
        }
    }
    ~BinaryStreamIn() {
        if (this->samplesInOneSecond != nullptr && this->samplesInOneSecond != NULL) {
            delete this->samplesInOneSecond;
        }
        if (this->header != nullptr) {
            delete this->header;
        }
    }
    WAVHeader * getHeader() { return header; }

    char * getSamplesInOneSecond();
    int parseMetadataInWavFile();

private:
    string fileName;
    WAVHeader *WAVheader;
//    WAVNeedsParameters *WAVNeedsparameters;
    size_t metadataSize = 0;
    char *samplesInOneSecond;

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

    void push(char *data, const size_t dataSize);

private:
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
