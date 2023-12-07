#include "Streams.h"
#include "Exceptions.h"
#include <vector>
#include "functional"
using std::function;
using std::cerr;
using std::endl;
using std::vector;

int BinaryStreamIn::openFile(const string &fileName) {
    int r;
    this->stream.open(fileName, std::ios::in | std::ios::binary);
    r = checkFileOpen(fileName);
    return r;
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

char * BinaryStreamIn::samplesInOneSecond = nullptr;
char *BinaryStreamIn::getSamplesInOneSecond(const size_t second, const size_t frequency,
                                            const size_t bitsPerSample) {

    this->stream.read(samplesInOneSecond, frequency * (bitsPerSample / BITS_PER_BYTE));

    return samplesInOneSecond;
}

int BinaryStreamIn::checkWavCorrectFormatFile(const size_t frequency, const size_t bitsPerSample,
                                           const size_t channels, const size_t audioFormat) {

    int r;
    function<int(void(*foo)(char data[4], BinaryStreamIn *ptr))> tryCatch;

    this->metadataSize = 8;

    char data[4];
    this->stream.read(data, 4);
    try {
        if (data != "RIFF") {
            throw IncorrectFileFormat(this->fileName);
        }
    } catch (IncorrectFileFormat  &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    this->stream.read(data, 4);
    unsigned int fileSize =  *reinterpret_cast<int*>(data) + 8;


    this->stream.read(data, 4);
    if ((r = tryCatch([](char data[4], BinaryStreamIn *ptr) { if (data != "fmt ") {
        throw IncorrectFileFormat(ptr->fileName);
    } })) != 0) { return r; }

    this->stream.read(data, 4);


    tryCatch = [&data, this](void(*foo)(char data[4], BinaryStreamIn *ptr)) {
        try {
            foo(data, this);
        } catch (IncorrectFileFormat  &ex) {
            cerr << ex.ex_what() << endl;
            return ex.getErrorCode();
        }
        return 0;
    };

    this->stream.seekg(0, this->stream.beg);
    return 0;
}
