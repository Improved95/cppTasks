#include "FilesParser.h"
#include "Converter.h"
#include "Streams.h"
#include "Exceptions.h"
using std::ifstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::initializeConvertersAndInitialConvert() {
    int r;
    NsuSoundProcessorConfigParser filesParser;

    StreamIn configFile(arguments[0], r);
    if (r != 0) { return r; }

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector)) != 0) { return r; }
    if (convertersVector.size() == 0) { return 0; }

    for (auto &el : convertersVector) {
        if ((r = el->parseParameters()) != 0) { return r; }
    }

    const size_t frequency = 44100;
    const size_t sampleSize = 16;
    const size_t metadataSizeInWav = 44;

    if ((r = NsuConverterI::initialInputStreams(convertersVector, arguments)) != 0) { return r; }
    if ((r = NsuConverterI::initialOutputStreams(arguments)) != 0) { return r; }
    NsuConverterI::setFrequency(frequency);
    NsuConverterI::setSizeOfSample(sampleSize);
    NsuConverterI::setMetadataSize(metadataSizeInWav);

//    convert(convertersVector);

    return r;
}

int NsuSoundProcessorManager::convert(vector<NsuConverterI*> &convertersVector) {
    while(!NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            el->convert();
        }
    }
    return 0;
}

bool NsuConverterI::convertersIsOver(const vector<NsuConverterI*> &convertersVector) {
    for (auto &el : convertersVector) {
        if (!el->convertingIsComplete) {
            return false;
        }
    }
    return true;
}

vector<BinaryStreamIn*> NsuConverterI::inputsVector = {};
int NsuConverterI::initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments) {
    int r = 0;
    vector<bool> inputIsOpen(arguments.size() - 2, false); // -2 потому что первые два аргумента это конфиг и аутпут
    for (auto &el : convertersVector) {

        try {
            if (el->usingStream.first > arguments.size() - 3) {
                throw NotEnoughInputsException(el->usingStream.first);
            }
        } catch (NotEnoughInputsException &ex) {
            cerr << ex.ex_what() << endl;
            return ex.getErrorCode();
        }

        if (!inputIsOpen[el->usingStream.first]) {
            BinaryStreamIn *temp = new BinaryStreamIn(arguments[el->usingStream.first + 2], r); // +2 потому что в аргументах первыми двумя лежат config и аутпут
            if (r != 0) { return r; }
            inputsVector.push_back(temp);
            inputIsOpen[el->usingStream.first] = true;
        }

        if ((el->createInputStreams(arguments, inputIsOpen)) != 0) { return r; }
    }
    return r;
}

int NsuMute::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen) {
    // функция пустышка
    int r;
    if (arguments[0] == "") { r = 0; }
    if (inputIsOpen[0] == false) { r = 0; }
    r = 0;
    return r;
}

int NsuMix::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen) {
    int r = 0;

    try {
        if (this->mixStream.first > arguments.size() - 3) {
            throw NotEnoughInputsException(this->mixStream.first);
        }
    } catch (NotEnoughInputsException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    if (!inputIsOpen[this->mixStream.first]) {
        BinaryStreamIn *temp = new BinaryStreamIn(arguments[this->mixStream.first + 2], r);
        if (r != 0) { return r; }
        inputsVector.push_back(temp);
        inputIsOpen[this->mixStream.first] = true;
    }

    return r;
}

BinaryStreamOut * NsuConverterI::output = nullptr;
int NsuConverterI::initialOutputStreams(vector<string> &arguments) {
    int r;
    BinaryStreamOut *temp = new BinaryStreamOut(arguments[1], r);
    if (r != 0) { return r; }
    output = temp;

    return r;
}

size_t NsuConverterI::frequency = 0;
size_t NsuConverterI::sampleSize = 0;
size_t NsuConverterI::metadataSize = 0;
size_t NsuConverterI::secondNumber = 0;
void NsuMute::convert() {

}

void NsuMix::convert() {

}
