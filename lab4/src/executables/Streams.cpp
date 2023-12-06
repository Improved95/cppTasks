#include "Streams.h"
#include "Exceptions.h"
#include <vector>
using std::cerr;
using std::endl;
using std::vector;

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

vector<Sample*> BinaryStreamIn::getSamplesInOneSecond(const size_t second, const size_t frequency,
                                                      const size_t sampleSizeInByte, const size_t metadataSize) {
    this->stream.seekg(metadataSize + frequency * sampleSizeInByte * second, this->stream.beg);

        vector<Sample*> samplesVector(frequency);
        for (size_t i = 0; i < frequency; i++) {
        samplesVector.push_back(new Sample(sampleSizeInByte));
    }

    return samplesVector;
}