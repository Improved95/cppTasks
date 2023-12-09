#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>
#include <unordered_map>
#include "cxxopts.hpp"
#include "Streams.h"
using std::vector;
using std::string;
using std::unordered_map;
using std::pair;

class NsuSoundProcessorManager;

class NsuConvertersInfo {
public:
    static const string * getConvertersName() { return convertersNames; }
    static const string & getConvertersNamesPatterns() { return ConvertersNamesPatterns; }
    static size_t getConvertersQuantity() { return convertersQuantity; }
protected:
    static const size_t convertersQuantity = 2;
    static const string convertersNames[convertersQuantity];
    static const string ConvertersNamesPatterns;
};

// ========================================== Converters Manager  ====================================
class NsuConverterI;
class NsuSoundProcessorManager {
public:
    NsuSoundProcessorManager(vector<string> &arguments_) {}

    int initializeConvertersAndInitialConvert();

private:
    vector<string> arguments;
    size_t createNumber = 0;
    bool convertingIsComplete;
    size_t secondNumber;
    vector<BinaryStreamIn*> inputsVector;
    BinaryStreamOut *output;

    int converting(vector<NsuConverterI*> &convertersVector);
    int initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments,
                                   const size_t sampleRate, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat);
    int initialOutputStreams(vector<string> &arguments);


};

// ======================================== Converters =============================================
class NsuConverterI : public NsuConvertersInfo {
public:
    NsuConverterI(const string &parameters_, const size_t createNumber_) {
        this->parameters = parameters_;
        this->createNumber = createNumber_;
    }

    pair<size_t, pair<size_t, size_t>> & getInputStreamInfo() { return this->inputStreamInfo; }

    virtual int convert() = 0;
    virtual int parseParameters() = 0;
    int checkParameters(vector<BinaryStreamIn*> &inputsVector);
    virtual int checkUniqueParameters(vector<BinaryStreamIn*> &inputsVector) = 0;
    virtual int initialUniqueInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen, vector<BinaryStreamIn*> &inputsVector,
                                   const size_t sampleRate, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat) = 0;

protected:
    string parameters;
    size_t createNumber = 0;
    /*first value: stream index in vector of streams; second value: <begin, end>*/
    pair<size_t, pair<size_t, size_t>> inputStreamInfo;

    int getParseResult(size_t parametersQuantity,
                         cxxopts::Options &options, cxxopts::ParseResult &result);
};

class NsuMute : public NsuConverterI {
public:
    NsuMute(const string &parameters, const size_t numberOfCreate) : NsuConverterI(parameters, numberOfCreate) {}

    virtual int convert() override;
    virtual int parseParameters() override;
    virtual int checkUniqueParameters(vector<BinaryStreamIn*> &inputsVector) override;
    int initialUniqueInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen, vector<BinaryStreamIn*> &inputsVector,
                                  const size_t sampleRate, const size_t bytePerSample,
                                  const size_t channels, const size_t audioFormat) override;
};

class NsuMix : public NsuConverterI {
public:
    NsuMix(const string &parameters, const size_t numberOfCreate) : NsuConverterI(parameters, numberOfCreate) {}

    virtual int convert() override;
    virtual int parseParameters() override;
    virtual int checkUniqueParameters(vector<BinaryStreamIn*> &inputsVector) override;
    int initialUniqueInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen, vector<BinaryStreamIn*> &inputsVector,
                                  const size_t sampleRate, const size_t bytePerSample,
                                  const size_t channels, const size_t audioFormat) override;

private:
    /*first value: stream index in vector of streams second value: seconds*/
    pair<size_t, size_t> mixStream;
};

#endif
