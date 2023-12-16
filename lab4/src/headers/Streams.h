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

class Sample {
public:
    Sample(const size_t sampleSize_) {
       this->sampleSize = sampleSize_;
       this->data = new char[this->sampleSize];
    }
    ~Sample() {
        delete[] this->data;
    }

    void operator+=(const Sample &s1);
    // void operator=(const Sample &s1);

    size_t getSampleSize() { return this->sampleSize; }
    char * getData() { return this->data; }

private:
    size_t sampleSize;
    char *data = nullptr;
};

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
    char subchunkRIFF[4];
    uint32_t fileSize;
    char format[4];

    char subchunkFmt[4];
    uint32_t subchunkFmtSize;
    uint16_t audioFormat;
    uint16_t numberOfChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t bytePerSample;
    uint16_t bitsPerSample;

    char subchunkData[4];
    uint32_t dataSize;
};

class BinaryStreamIn : public Stream, public CompareString {
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

    int getSample(Sample &temp, const size_t sampleNumber);
    int getSample(Sample &temp);
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
    
    void pushInFile(char *data, const size_t dataSize);

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
