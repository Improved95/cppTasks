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

// ========================================== Converters Manager  ==========================================
class NsuConverterI;
class NsuSoundProcessorManager {
public:
    NsuSoundProcessorManager(vector<string> &arguments_) {}

    int initializeConvertersAndInitialConvert();

private:
    vector<string> arguments;
    int convert(vector<NsuConverterI*> &convertersVector);
};

// ======================================== Converters =============================================

class NsuConverterI : public NsuConvertersInfo {
public:
    static size_t t1;

    NsuConverterI(const string &parameters_) {
        this->numberOfCreate = orderCreation;
        this->orderCreation++;
        this->parameters = parameters_;
    }

    virtual int convert() = 0;
    virtual int parseParameters() = 0;
    int checkParameters();
    virtual int checkUniqueParameters() = 0;

    static int initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments,
                                   const size_t frequency, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat);
    static int initialOutputStreams(vector<string> &arguments);

    static BinaryStreamOut *output;
private:
    virtual int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                                   const size_t frequency, const size_t bytePerSample,
                                   const size_t channels, const size_t audioFormat) = 0;

protected:
    string parameters;
    size_t numberOfCreate = 0;
    /*первое значение: индекс потока в векторе входных потоков
     второе значение: <начало(секунда), конец(секунда)>*/
    pair<size_t, pair<size_t, size_t>> inputStreamInfo;

    static size_t orderCreation;
    static bool convertingIsComplete;
    static size_t secondNumber;
    static size_t readDataSize;
    static vector<BinaryStreamIn*> inputsVector;

    int fillUsingThreads(size_t parametersQuantity,
                         cxxopts::Options &options, cxxopts::ParseResult &result);

    friend NsuSoundProcessorManager;
};

class NsuMute : public NsuConverterI {
public:
    NsuMute(const string &parameters) : NsuConverterI(parameters) {}

    virtual int convert() override;
    virtual int parseParameters() override;
    virtual int checkUniqueParameters() override;

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
    virtual int checkUniqueParameters() override;

private:
    /*первое значение: индекс потока в векторе входных потоков
     второе значение: сколько секунд*/
    pair<size_t, size_t> mixStream;
    static const string parametersPattern;

    int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen,
                           const size_t frequency, const size_t bytePerSample,
                           const size_t channels, const size_t audioFormat) override;
};

#endif
