#include <iostream>
using std::ifstream;



class IConverter {
    virtual void takeSampleFromInput(ifstream &input);
};

class Mute : IConverter {

};

class ConverterManager {

};