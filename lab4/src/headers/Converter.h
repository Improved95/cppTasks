#ifndef CONVERTER
#define CONVERTER

#include <iostream>
#include <vector>
using std::ifstream;
using std::vector;

class IConverter {
    virtual void takeSampleFromInput(ifstream &input);
};

class Mute : IConverter {

};

class Mix : IConverter {

};

class ConverterManager {
public:
    void initialConverterManager();
};

#endif
