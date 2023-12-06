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
    BinaryStreamIn(const string &fileName, size_t frequency, size_t sampleSizeInByte, int &r) {
        r = openFile(fileName);

        if (samplesInOneSecond == nullptr) {
            samplesInOneSecond = new char[frequency * sampleSizeInByte];
            if (samplesInOneSecond == NULL) { r = 6; }
        }
    }
    ~BinaryStreamIn() {
        if (this->samplesInOneSecond != nullptr && this->samplesInOneSecond != NULL) {
            delete samplesInOneSecond;
        }
    }

    char * getSamplesInOneSecond(const size_t second, const size_t frequency,
                                 const size_t sampleSizeInByte, const size_t metadataSize);

private:
    static char *samplesInOneSecond;
    virtual int openFile(const string &fileName) override;
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
