#include "Streams.h"
#include "Exceptions.h"
using std::cerr;
using std::endl;

/*
void StreamIn::setPointer(size_t pos) {
    this->streamIn->seekg(pos, this->streamIn->beg);
}
*/

int BinaryStreamIn::openFile(const string &fileName) {
    this->stream.open(fileName, std::ios::in | std::ios::binary);
    return checkFileOpen(fileName);
}

int BinaryStreamOut::openFile(const string &fileName) {
    this->stream.open(fileName, std::ios::out | std::ios::binary);
    return checkFileOpen(fileName);
}

int StreamIn::openFile(const std::string &fileName) {
    this->stream.open(fileName, std::ios::in);
    return checkFileOpen(fileName);
}

int Stream::checkFileOpen(const string &fileName) {
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


