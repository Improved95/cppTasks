#include "Streams.h"
#include "Exceptions.h"
using std::cerr;
using std::endl;

/*
void StreamIn::setPointer(size_t pos) {
    this->streamIn->seekg(pos, this->streamIn->beg);
}
*/


int StreamIn::openFile(const string &fileName) {
    this->stream.open(fileName, std::ios::in | std::ios::binary);
    return fileOpenException(fileName);
}

int StreamOut::openFile(const string &fileName) {
    this->stream.open(fileName, std::ios::out | std::ios::binary);
    return fileOpenException(fileName);
}


int Stream::fileOpenException(const string &fileName) {
    try {
        if (!this->stream.is_open()) {
            throw FileNotOpenException(fileName);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    return 0;
}
