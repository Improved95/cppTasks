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
    uint32_t chunkSize; //размер файла минус 8
    char format[4]; //формат (WAVE)

    char subchunkFmt[4]; // название секции, должна быть fmt
    uint32_t subchunk1Size; //размер данных fmt
    uint16_t audioFormat; //формат аудиоданных
    uint16_t numChannels; //кол-во аудиоканалов
    uint32_t sampleRate; //частота дискретизации
    uint32_t byteRate; //байтовая скорость
    uint16_t bytePerSample; //кол-во байтов для одного сэмпла
    uint16_t bitsPerSample; //кол-во битов для сэмпла

    char subchunk2ID[4]; //идентификатор второй подчасти
    uint32_t subchunk2Size; //размер данных в этой подчасти
};

struct WAVNeedsParameters {
    size_t frequency;
    size_t bytePerSample;
    size_t numberOfChannels;
    size_t audioFormat;
    size_t metadataSize;
};

class BinaryStreamIn : public Stream, public CompareString {
public:
    BinaryStreamIn(const string &fileName_, const size_t frequency_, const size_t bytePerSample_,
    const size_t channels_, const size_t audioFormat_, int &r) {
        r = openFile(fileName_);
        this->WAVparameters = new WAVNeedsParameters;
        this->WAVparameters->frequency = frequency_;
        this->WAVparameters->bytePerSample = bytePerSample_;
        this->WAVparameters->numberOfChannels = channels_;
        this->WAVparameters->audioFormat = audioFormat_;

        this->fileName = fileName_;
    }
    ~BinaryStreamIn() {
        if (this->samplesInOneSecond != nullptr && this->samplesInOneSecond != NULL) {
            delete this->samplesInOneSecond;
        }
        if (this->header != nullptr) {
            delete this->header;
        }
    }

    char * getSamplesInOneSecond();
    int parseMetadataInWavFile();

private:
    string fileName;
    WAVHeader *header;
    WAVNeedsParameters *WAVparameters;
    char *samplesInOneSecond;

    virtual int openFile(const string &fileName) override;

    friend ParserRIFF;
    friend ParserFmt;
    friend ParserLIST;
};

class BinaryStreamOut : public Stream {
public:
    BinaryStreamOut(const string &fileName, int &r) {
        r = openFile(fileName);
    }

    void pushSample();

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
