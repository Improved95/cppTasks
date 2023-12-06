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
        this->priority = orderCreation;
        this->orderCreation++;
        this->parameters = parameters_;
    }

    static void setFrequency(const size_t frequency_) { frequency = frequency_; }
    static void setSizeOfSample(const size_t sampleSize_) { sampleSizeInByte = sampleSize_; }
    static void setMetadataSize(const size_t metadataSize_) { metadataSize = metadataSize_; }

    virtual int parseParameters() = 0;
    virtual void convert() = 0;

    static int initialInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments);
    static int initialOutputStreams(vector<string> &arguments);
    static bool convertersIsOver(const vector<NsuConverterI*> &convertersVector);

private:
    static size_t orderCreation;
    virtual int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen) = 0;

protected:
    string parameters;

    size_t priority = 0;
    bool convertingIsComplete = false;
    pair<size_t, pair<size_t, size_t>> usingStream;

    static size_t frequency;
    static size_t sampleSizeInByte;
    static size_t metadataSize;
    static size_t secondNumber;
    static vector<BinaryStreamIn*> inputsVector;
    static BinaryStreamOut *output;

    int fillUsingThreads(size_t parametersQuantity,
                         cxxopts::Options &options, cxxopts::ParseResult &result);
};

class NsuMute : public NsuConverterI {
public:
    NsuMute(const string &parameters) : NsuConverterI(parameters) {}

    virtual void convert() override;
    virtual int parseParameters() override;

private:
    static const string parametersPattern;

    int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen) override;
};

class NsuMix : public NsuConverterI {
public:
    NsuMix(const string &parameters) : NsuConverterI(parameters) {}

    virtual void convert() override;
    virtual int parseParameters() override;

private:
    pair<size_t, size_t> mixStream;
    static const string parametersPattern;

    int createInputStreams(vector<string> &arguments, vector<bool> &inputIsOpen) override;
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
};

#endif

/*
 * пусть конвертеры хранят приоритеты и то, с чем они работают, другие конвертеры будут
 * знать приоритеты других и с чем они работают
 * буду пускать streamOut по конвертерам aka по кругу и пусть каждый конвертер проверяет
 * может ли он сейчас отработать с сэмплом или нет, может ли он записать сейчас в output
 * отработанный сэмпл или нет
 * */