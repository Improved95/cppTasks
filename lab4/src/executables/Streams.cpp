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
                                           const size_t numberOfChannels, const size_t compressingCode) {
    this->metadataSize = 8;
    function<bool(const string &s1, const string &s2)> strIsEqual = [](const string &s1, const string &s2) {
        if (s1 == s2) {
            return true;
        }
        return false;
    };

    //RIFF
    char data[4];
    this->stream.read(data, 4);
    try {
        if (!strIsEqual(data, "RIFF")) {
            throw IncorrectFileFormat(this->fileName);
        }
    } catch (IncorrectFileFormat &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    //Считываю размер файла
    this->stream.read(data, 4);
    unsigned int fileSize =  *reinterpret_cast<int*>(data) + 8;

    //проверяю WAVE
    this->stream.read(data, 4);
    try {
        if (strIsEqual(data, "WAVE")) {
            throw IncorrectFileFormat(this->fileName);
        }
    } catch (IncorrectFileFormat &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    //проверяю fmt
    this->stream.read(data, 4);
    try {
        if (strIsEqual(data, "fmt ")) {
            throw IncorrectFileFormat(this->fileName);
        }
    } catch (IncorrectFileFormat &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    //считываю размер данных блока fmt
    this->stream.read(data, 4);
    this->metadataSize += *reinterpret_cast<int*>(data);

    //считываю код сжатия
    this->stream.read(data, 2);
    int dataInt = *reinterpret_cast<int*>(data);
    try {
        if (dataInt != compressingCode) {
            throw IncorrectFileFormat(this->fileName, "compressing code");
        }
    } catch (IncorrectFileFormat &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    //считываю количество каналов
    this->stream.read(data, 2);
    dataInt = *reinterpret_cast<int*>(data);
    try {
        if (dataInt != compressingCode) {
            throw IncorrectFileFormat(this->fileName, "number of channels");
        }
    } catch (IncorrectFileFormat &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    this->stream.seekg(0, this->stream.beg);
    return 0;
}
