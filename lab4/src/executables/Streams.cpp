#include "Streams.h"
#include "Exceptions.h"
#include <vector>
#include "WavMetadataParse.h"
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

int BinaryStreamIn::getSample(Sample &temp, const size_t filePlace) {
    this->stream.seekg(this->metadataSize + (filePlace * this->WAVheader->sampleRate * this->WAVheader->bytePerSample), this->stream.beg);
    this->stream.read(reinterpret_cast<char*>(temp.getData()), this->WAVheader->bytePerSample);
    return this->stream.gcount();
}

int BinaryStreamIn::getSample(Sample &temp) {
    this->stream.read(reinterpret_cast<char*>(temp.getData()), this->WAVheader->bytePerSample);
    return this->stream.gcount();
}

void BinaryStreamOut::pushInFile(char *data, const size_t dataSize) {
    this->stream.write(data, dataSize);
}
