#ifndef STREAMS
#define STREAMS

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;

class Stream {
public:
    ~Stream() {
        this->stream.close();
    }

    fstream & getStream() { return this->stream; }
    int fileOpenException(const string &fileName);

protected:
    fstream stream;
    virtual int openFile(const string &fileName) = 0;
};

class StreamIn : public Stream {
public:
    StreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

class StreamOut : public Stream {
public:
    StreamOut(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

#endif
