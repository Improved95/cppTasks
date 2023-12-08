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

    const size_t sampleRate = 44100;
    const size_t bytePerSample = 2;
    const size_t numberOfchannels = 1;
    const size_t compressedCode = 1;

    if ((r = NsuConverterI::initialInputStreams(convertersVector, arguments, sampleRate, bytePerSample, numberOfchannels, compressedCode)) != 0) { return r; }
    if ((r = NsuConverterI::initialOutputStreams(arguments)) != 0) { return r; }
    BinaryStream::setSampleBuffer(sampleRate * bytePerSample);

    convert(convertersVector);

    return r;
}

int NsuSoundProcessorManager::convert(vector<NsuConverterI*> &convertersVector) {
    int r;
//    NsuConverterI::output->getStream().close();
//    exit(-1);
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
                                       const size_t sampleRate, const size_t bytePerSample,
                                       const size_t channels, const size_t audioFormat) {
    int r = 0;
    vector<bool> inputIsOpen(arguments.size() - 2, false); // -2 потому что первые два аргумента это конфиг и аутпут
    for (auto &el : convertersVector) {

        try {
            if (el->inputStreamInfo.first > arguments.size() - 3) {
                throw NotEnoughInputsException(el->inputStreamInfo.first);
            }
        } catch (NotEnoughInputsException &ex) {
            cerr << ex.ex_what() << endl;
            return ex.getErrorCode();
        }

        if (!inputIsOpen[el->inputStreamInfo.first]) {
            BinaryStreamIn *temp = new BinaryStreamIn(arguments[el->inputStreamInfo.first + 2], r); // +2 потому что в аргументах первыми двумя лежат config и аутпут
            if (r != 0) { return r; }
            inputsVector.push_back(temp);
            inputIsOpen[el->inputStreamInfo.first] = true;

            //делаю различные проверки
            if ((r = temp->parseMetadataInWavFile(sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
            el->checkParameters();
        }

        if ((r = el->createInputStreams(arguments, inputIsOpen, sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
    }
    return r;
}

int NsuMute::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                                const size_t sampleRate, const size_t bytePerSample,
                                const size_t channels, const size_t audioFormat) {
    // функция пустышка
    int r;
    if (arguments[0] == "" && sampleRate == 0 && bytePerSample == 0
        && channels == 0 && audioFormat == 0) { r = 0; }
    if (inputIsOpen[0] == false) { r = 0; }
    r = 0;
    return r;
}

int NsuMix::createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                               const size_t sampleRate, const size_t bytePerSample,
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
        BinaryStreamIn *temp = new BinaryStreamIn(arguments[this->mixStream.first + 2], r);
        if (r != 0) { return r; }
        inputsVector.push_back(temp);
        inputIsOpen[this->mixStream.first] = true;

        //делаю различные проверки
        if ((r = temp->parseMetadataInWavFile(sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
        this->checkUniqueParameters();
    }

    return r;
}

BinaryStreamOut * NsuConverterI::output = nullptr;
int NsuConverterI::initialOutputStreams(vector<string> &arguments) {
    int r;
    BinaryStreamOut *temp = new BinaryStreamOut(arguments[1], r);
    if (r != 0) { return r; }
    output = temp;
    output->pushInFile(reinterpret_cast<char*>(NsuConverterI::inputsVector[0]->getHeader()), sizeof(WAVHeader));

    return r;
}
