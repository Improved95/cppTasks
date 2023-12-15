#include "FilesParser.h"
#include "Converter.h"
#include "Streams.h"
#include "Exceptions.h"
using std::ifstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::initializeConvertersAndInitialConvert(vector<string> &arguments) {
    int r;
    NsuSoundProcessorConfigParser filesParser;

    StreamIn configFile(arguments[0], r);
    if (r != 0) { return r; }

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector, this->createNumber)) != 0) { return r; }
    if (convertersVector.size() == 0) { return 0; }

    for (auto &el : convertersVector) {
        if ((r = el->parseParameters()) != 0) { return r; }
    }

    const size_t sampleRate = 44100;
    const size_t bytePerSample = 2;
    const size_t numberOfchannels = 1;
    const size_t compressedCode = 1;

    if ((r = initialInputStreams(convertersVector, arguments, sampleRate, bytePerSample, numberOfchannels, compressedCode)) != 0) { return r; }
    if ((r = initialOutputStreams(arguments)) != 0) { return r; }

    converting(convertersVector);

    return r;
}

int NsuSoundProcessorManager::initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments,
                                       const size_t sampleRate, const size_t bytePerSample,
                                       const size_t channels, const size_t audioFormat) {
    int r = 0;
    vector<bool> inputIsOpen(arguments.size() - 2, false); // -2 потому что первые два аргумента это конфиг и аутпут
    for (auto &el : convertersVector) {
        try {
            if (el->getInputStreamInfo().first > arguments.size() - 3) {
                throw NotEnoughInputsException(el->getInputStreamInfo().first);
            }
        } catch (NotEnoughInputsException &ex) {
            cerr << ex.ex_what() << endl;
            return ex.getErrorCode();
        }

        if (!inputIsOpen[el->getInputStreamInfo().first]) {
            BinaryStreamIn *temp = new BinaryStreamIn(arguments[el->getInputStreamInfo().first + 2], r); // +2 потому что в аргументах первыми двумя лежат config и аутпут
            if (r != 0) { return r; }
            this->inputsVector.push_back(temp);
            inputIsOpen[el->getInputStreamInfo().first] = true;

            if ((r = temp->parseMetadataInWavFile(sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
            el->checkParameters(this->inputsVector);
        }

        if ((r = el->initialUniqueFields(arguments, inputIsOpen, this->inputsVector, sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
    }
    return r;
}

int NsuMute::initialUniqueFields(vector<string> &, vector<bool> &, vector<BinaryStreamIn*> &, const size_t,
                                       const size_t, const size_t, const size_t) {
    return 0;
}

int NsuMix::initialUniqueFields(vector<string> &arguments, vector<bool> &inputIsOpen, vector<BinaryStreamIn*> &inputsVector,
                                        const size_t sampleRate, const size_t bytePerSample,
                                        const size_t channels, const size_t audioFormat) {
    int r = 0;

    //initial unique mix stream
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

        if ((r = temp->parseMetadataInWavFile(sampleRate, bytePerSample, channels, audioFormat)) != 0) { return r; }
        this->checkUniqueParameters(inputsVector);
        this->mixSample = new Sample(inputsVector[this->inputStreamInfo.first]->getHeader()->bytePerSample);
    }

    return r;
}

int Delay::initialUniqueFields(vector<string> &, vector<bool> &, vector<BinaryStreamIn*> &inputsVector, const size_t,
                                       const size_t, const size_t, const size_t) {

    WAVHeader *wavInfo =  inputsVector[this->inputStreamInfo.first]->getHeader();
    double a = (this->timeOfOneEcho + this->temp) / 1000.0;
    this->samplesPerEcho = wavInfo->sampleRate * a;
    for (size_t i = 0; i < (this->inputStreamInfo.second.second - this->inputStreamInfo.second.first) / (this->timeOfOneEcho / 1000); i++) {
        this->echosInfo.push_back(pair(this->feedBack, false));
    }

    return 0;
}

int NsuSoundProcessorManager::initialOutputStreams(vector<string> &arguments) {
    int r;
    BinaryStreamOut *temp = new BinaryStreamOut(arguments[1], r);
    if (r != 0) { return r; }
    output = temp;
    output->pushInFile(reinterpret_cast<char*>(NsuSoundProcessorManager::inputsVector[0]->getHeader()), sizeof(WAVHeader));

    return r;
}
