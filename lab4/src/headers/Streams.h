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

protected:
    fstream stream;
    virtual int openFile(const string &fileName) = 0;
    int checkFileOpen(const string &fileName);
};

class NsuStreamIn : public Stream {
public:
    NsuStreamIn(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

class NsuStreamOut : public Stream {
public:
    NsuStreamOut(const string &fileName, int &r) {
        r = openFile(fileName);
    }

private:
    virtual int openFile(const string &fileName) override;
};

#endif
