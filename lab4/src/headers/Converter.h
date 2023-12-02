#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>
using std::vector;
using std::string;
using std::move;

class Converter {

};

class MuteConverter : Converter {

};

class MixConverter : Converter {

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

#endif


/*
 * пусть конвертеры хранят приоритеты и то, с чем они работают, другие конвертеры будут
 * знать приоритеты других и с чем они работают
 * буду пускать streamOut по конвертерам aka по кругу и пусть каждый конвертер проверяет
 * может ли он сейчас отработать с сэмплом или нет, может ли он записать сейчас в output
 * отработанный сэмпл или нет
 * */