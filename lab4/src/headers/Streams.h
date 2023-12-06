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

class Sample;
class BinaryStreamIn : public Stream {
public:
    BinaryStreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }

    vector<Sample*> getSamplesInOneSecond(const size_t second, const size_t frequency,
                                          const size_t sampleSizeInByte, const size_t metadataSize);

private:

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

class Sample {
public:
    Sample(size_t sampleSize) {
        bytesArray = new char[sampleSize];
    }
    ~Sample() {
        delete bytesArray;
    }

private:
    char *bytesArray;
};

#endif
