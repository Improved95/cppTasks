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

class NsuConverterI : public NsuConvertersInfo {
public:
    NsuConverterI(const string &parameters_) {
        this->numberOfCreate = orderCreation;
        this->orderCreation++;
        this->parameters = parameters_;
    }

    virtual int parseParameters() = 0;
    virtual int convert() = 0;

    static int initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments,
                                   const size_t frequency, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat);
    static int initialOutputStreams(vector<string> &arguments);
    static bool convertersIsOver(const vector<NsuConverterI*> &convertersVector);

private:
    static size_t orderCreation;
    virtual int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                                   const size_t frequency, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat) = 0;

protected:
    string parameters;

    size_t numberOfCreate = 0;
    bool convertingIsComplete = false;
    pair<size_t, pair<size_t, size_t>> usingStream;

    static size_t secondNumber;
    static vector<BinaryStreamIn*> inputsVector;
    static BinaryStreamOut *output;

    int fillUsingThreads(size_t parametersQuantity,
                         cxxopts::Options &options, cxxopts::ParseResult &result);

    friend NsuSoundProcessorManager;
};

class NsuMute : public NsuConverterI {
public:
    NsuMute(const string &parameters) : NsuConverterI(parameters) {}

    virtual int convert() override;
    virtual int parseParameters() override;

private:
    static const string parametersPattern;

    int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                           const size_t frequency, const size_t bytePerSample,
                           const size_t channels, const size_t audioFormat) override;
};

class NsuMix : public NsuConverterI {
public:
    NsuMix(const string &parameters) : NsuConverterI(parameters) {}

    virtual int convert() override;
    virtual int parseParameters() override;

private:
    pair<size_t, size_t> mixStream;
    static const string parametersPattern;

    int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                           const size_t frequency, const size_t bytePerSample,
                           const size_t channels, const size_t audioFormat) override;
};


// ========================================== Converters Manager  ==========================================
class ConvertesManagers {
public:
    ConvertesManagers(vector<string> &arguments_) {
        this->arguments = std::move(arguments_);
    }

    virtual int initializeConvertersAndInitialConvert() = 0;

protected:
    vector<string> arguments;

    virtual int convert(vector<NsuConverterI*> &convertersVector) = 0;
};

class NsuSoundProcessorManager : public ConvertesManagers{
public:
    NsuSoundProcessorManager(vector<string> &arguments_) : ConvertesManagers(arguments_){}

    virtual int initializeConvertersAndInitialConvert() override;

private:
    virtual int convert(vector<NsuConverterI*> &convertersVector) override;
    int checkFilesFormatAndParameters(vector<NsuConverterI*> convertersVector);
};

#endif
