#include "FilesParser.h"
#include "Exceptions.h"
#include "Converter.h"
#include "ConvertersFactory.h"
using std::ifstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::convert() {
    int r;
    NsuSoundProcessorConfigParser filesParser;


    ifstream configFile;
    try {
        configFile.open(arguments[0]);
        if (!configFile.is_open()) {
            throw FileNotOpenException(arguments[0]);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    NsuConvertersFactory factory;
    vector<NsuConverterI*> convertersVector;
    convertersVector.push_back(factory.create("mix"));

//    r = filesParser.parse(configFile, convertersVector);



    configFile.close();
    return r;
}


size_t NsuConverterI::orderCreation = 0;
const string NsuConverterI::patternsOfConverterNamesWithParameters[convertersQuantity] =
        {"mute [0-9]+ [0-9]+", "mix [0-9]+ [0-9]+ [$][0-9]+ [0-9]+"};

void NsuMute::parseParameters() {

}

void NsuMix::parseParameters() {

}

void NsuMute::convert() {

}

void NsuMix::convert() {

}
