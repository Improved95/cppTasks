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

class StreamIn : public Stream {
public:
    StreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

class BinaryStreamIn : public Stream {
public:
    BinaryStreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }
    ~BinaryStreamIn() {
        if (this->samplesInOneSecond != nullptr && this->samplesInOneSecond != NULL) {
            delete samplesInOneSecond;
        }
    }

    char * getSamplesInOneSecond(const size_t second, const size_t frequency,
                                 const size_t bitsPerSample);

private:
    size_t metadataSize = 0;
    static char *samplesInOneSecond;

    virtual int openFile(const string &fileName) override;
    int checkCorrectFormatFile(const size_t frequency, const size_t bitsPerSample,
                               const size_t channels, const size_t audioFormat);
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


#endif
