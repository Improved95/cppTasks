#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>
#include <unordered_map>
#include "cxxopts.hpp"
using std::vector;
using std::string;
using std::unordered_map;
using std::pair;

class NsuConvertersInfo {
public:
    static const string * getConvertersName() { return convertersNames; }
    static const string & getConvertersNamesPatterns() { return ConvertersNamesPatterns; }
    static const size_t getConvertersQuantity() { return convertersQuantity; };
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

    virtual int parseParameters() = 0;
    virtual void convert() = 0;

    static bool convertersIsOver(const vector<NsuConverterI*> &convertersVector);

public:
    static size_t orderCreation;

    string parameters;
    size_t priority = 0;
    bool convertingIsComplete = false;
    pair<size_t, pair<size_t, size_t>> usingStream;

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
};

class NsuMix : public NsuConverterI {
public:
    NsuMix(const string &parameters) : NsuConverterI(parameters) {}

    virtual void convert() override;
    virtual int parseParameters() override;

private:
    pair<size_t, size_t> mixStream;
    static const string parametersPattern;
};

class ConvertesManagers {
public:
    ConvertesManagers(vector<string> &arguments_) {
        this->arguments = std::move(arguments_);
    }

    virtual int convert() = 0;

protected:
    vector<string> arguments;
};

class NsuSoundProcessorManager : public ConvertesManagers{
public:
    NsuSoundProcessorManager(vector<string> &arguments_) : ConvertesManagers(arguments_){}
    virtual int convert() override;
};

#endif

/*
 * пусть конвертеры хранят приоритеты и то, с чем они работают, другие конвертеры будут
 * знать приоритеты других и с чем они работают
 * буду пускать streamOut по конвертерам aka по кругу и пусть каждый конвертер проверяет
 * может ли он сейчас отработать с сэмплом или нет, может ли он записать сейчас в output
 * отработанный сэмпл или нет
 * */