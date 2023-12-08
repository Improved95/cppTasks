#ifndef STREAMS
#define STREAMS

#include <iostream>
#include <fstream>
#include <vector>
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
    char chunkID[4]; //RIFF
    uint32_t chunkSize; //размер файла минус 8
    char format[4]; //формат (WAVE)
    char subchunk1ID[4]; // название секции, должна быть fmt
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

class BinaryStreamIn : public Stream {
public:
    BinaryStreamIn(const string &fileName_, int &r) {
        r = openFile(fileName_);
        this->fileName = fileName_;
    }
    ~BinaryStreamIn() {
        if (this->samplesInOneSecond != nullptr && this->samplesInOneSecond != NULL) {
            delete samplesInOneSecond;
        }
    }

    char * getSamplesInOneSecond(const size_t second, const size_t frequency,
                                 const size_t bitsPerSample);
    int parseMetadataInWavFile(const size_t frequency, const size_t bitsPerSample,
                               const size_t channels, const size_t audioFormat);

private:
    size_t metadataSize = 0;
    size_t fileSize;
    string fileName;
    WAVHeader *header;
    char *samplesInOneSecond;

    virtual int openFile(const string &fileName) override;

    friend class ParseRIFF;
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
