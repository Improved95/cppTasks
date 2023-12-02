#ifndef STREAMS
#define STREAMS

#include <fstream>
using std::ifstream;
using std::ofstream;

class Stream {

};

class StreamIn : public Stream {
private:
    ifstream *streamIn;
};

class StreamOut : public Stream {
private:
    ofstream *streamOut;
public:
    void pushInStream(/*sample*/);
};

#endif
