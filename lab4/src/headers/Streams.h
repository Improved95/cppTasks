#ifndef STREAMS
#define STREAMS

#include <fstream>
#include <Exceptions.h>
using std::ifstream;
using std::ofstream;
using std::string;
using std::cerr;

class Stream {

};

class StreamIn : public Stream {
private:
    ifstream *streamIn;
};

class StreamOut : public Stream {
public:
    StreamOut(ofstream *streamOut_) {
        streamOut = streamOut_;
    }

    void pushInStream(/*sample*/);


private:
    ofstream *streamOut;
};

#endif
