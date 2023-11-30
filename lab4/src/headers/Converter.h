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
