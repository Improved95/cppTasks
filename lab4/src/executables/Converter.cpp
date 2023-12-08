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
    const size_t bytePerSample = 2;
    const size_t numberOfchannels = 1;
    const size_t compressedCode = 1;

    if ((r = NsuConverterI::initialInputStreams(convertersVector, arguments, frequency, bytePerSample, numberOfchannels, compressedCode)) != 0) { return r; }
    if ((r = NsuConverterI::initialOutputStreams(arguments)) != 0) { return r; }
    r = checkFilesFormatAndParameters(convertersVector);
    convert(convertersVector);

    return r;
}

WAVHeader * NsuConverterI::wavInfo = nullptr;
int NsuSoundProcessorManager::checkFilesFormatAndParameters(vector<NsuConverterI*> convertersVector) {
    int r;
    for (auto &el : NsuConverterI::inputsVector) {
        if ((r = el->parseMetadataInWavFile()) != 0) { return r; }
    }

    for (auto &el : convertersVector) {
        try {
            if (el->usingStream.second.first > el->usingStream.second.second) {
                throw IncorrectParametersFormatException(el->parameters, "Incorrect borders");
            }
        } catch (IncorrectParametersFormatException &ex) {
            cerr << ex.what() << endl;
            return ex.getErrorCode();
        }

        el->wavInfo = NsuConverterI::inputsVector[el->usingStream.first]->getHeader();;
        try {
            if (el->usingStream.second.second > (el->wavInfo->dataSize / el->wavInfo->frequency / el->wavInfo->bytePerSample)) {
                throw IncorrectParametersFormatException(el->parameters, "Incorrect borders, you out from file border.");
            }
        } catch (IncorrectParametersFormatException &ex) {
            cerr << ex.what() << endl;
            return ex.getErrorCode();
        }
    }


    return r;
}

int NsuSoundProcessorManager::convert(vector<NsuConverterI*> &convertersVector) {
    int r;
    while(!NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            if ((r = el->convert()) != 0) { return r; }
        }
    }
    return r;
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
int NsuConverterI::initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments,
                                       const size_t frequency, const size_t bytePerSample,
                                       const size_t channels, const size_t audioFormat) {
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
            BinaryStreamIn *temp = new BinaryStreamIn(arguments[el->usingStream.first + 2], frequency, bytePerSample, channels, audioFormat, r); // +2 потому что в аргументах первыми двумя лежат config и аутпут
            if (r != 0) { return r; }
            inputsVector.push_back(temp);
            inputIsOpen[el->usingStream.first] = true;

        }

        if ((r = el->createInputStreams(arguments, inputIsOpen, frequency, bytePerSample, channels, audioFormat)) != 0) { return r; }
    }
    return r;
}

int NsuMute::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                                const size_t frequency, const size_t bytePerSample,
                                const size_t channels, const size_t audioFormat) {
    // функция пустышка
    int r;
    if (arguments[0] == "" && frequency == 0 && bytePerSample == 0
        && channels == 0 && audioFormat == 0) { r = 0; }
    if (inputIsOpen[0] == false) { r = 0; }
    r = 0;
    return r;
}

int NsuMix::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                               const size_t frequency, const size_t bytePerSample,
                               const size_t channels, const size_t audioFormat) {
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
        BinaryStreamIn *temp = new BinaryStreamIn(arguments[this->mixStream.first + 2], frequency, bytePerSample, channels, audioFormat, r);
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

size_t NsuConverterI::secondNumber = 0;
int NsuMute::convert() {
    if (secondNumber >= this->usingStream.second.first && secondNumber <= this->usingStream.second.second) {
//        char *samplesArray = inputsVector[this->usingStream.first]->getSamplesInOneSecond(secondNumber, 10, 10);
//        try {
//            if (!inputsVector[this->usingStream.first]) {
//                throw RangeException(this->parameters);
//            }
//        } catch (RangeException &ex) {
//            cerr << ex.ex_what() << endl;
//            return ex.getErrorCode();
//        }
//        cerr << samplesArray << endl;
    }

    return 0;
}

int NsuMix::convert() {
    return 0;
}
