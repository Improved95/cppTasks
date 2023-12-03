#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>
#include <unordered_map>
#include "FilesParser.h"
using std::vector;
using std::string;
using std::move;
using std::unordered_map;
using std::pair;

class NsuConverterI {
public:
    NsuConverterI(const string &parameters) {
        this->parameters = parameters;
        this->priority = orderCreation;
        this->orderCreation++;
    }

    virtual void parseParameters() = 0;
    virtual void convert() = 0;

protected:
    static size_t orderCreation;

    string parameters;
    size_t priority = 0;
    bool convertingIsComplete = false;
    unordered_map<size_t, pair<size_t, size_t>> busyThreads;
};

class NsuMute : public NsuConverterI {
public:
    NsuMute(const string &parameters) : NsuConverterI(parameters) {}

    virtual void convert() override;
    virtual void parseParameters() override;
};

class NsuMix : public NsuConverterI {
public:
    NsuMix(const string &parameters) : NsuConverterI(parameters) {}

    virtual void convert() override;
    virtual void parseParameters() override;
};

class ConvertesManagers {
public:
    ConvertesManagers(vector<string> &arguments_) {
        this->arguments = move(arguments_);
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

/*====================================================================================*/

class NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters) const = 0;
};

template <class T>
class NsuConverterCreator : public NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters) const override {
        return new T(parameters);
    }
};

class NsuConvertersFactory {
public:
    NsuConvertersFactory() {
        add<NsuMute>("mute");
        add<NsuMix>("mix");
    }

    template<class T>
    void add(const string &converterName) {
        auto it = convetersRegistry.find(converterName);
        if (it == convetersRegistry.end()) {
            convetersRegistry[converterName] = new NsuConverterCreator<T>();
        }
    }

    NsuConverterI * create(const string &converterName) {
        auto it = convetersRegistry.find(converterName);
        if (it != convetersRegistry.end()) {
            return it->second->createConverter(converterName);
        }
        return nullptr;
    }

private:
    unordered_map<string, NsuConverterCreatorI*> convetersRegistry;
};

#endif


/*
 * пусть конвертеры хранят приоритеты и то, с чем они работают, другие конвертеры будут
 * знать приоритеты других и с чем они работают
 * буду пускать streamOut по конвертерам aka по кругу и пусть каждый конвертер проверяет
 * может ли он сейчас отработать с сэмплом или нет, может ли он записать сейчас в output
 * отработанный сэмпл или нет
 * */