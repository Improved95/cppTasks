#include <fstream>
#include "Converter.h"
#include "FilesParser.h"
#include "Exceptions.h"
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

    vector<string> parameters;
    vector<NsuConverterI*> convertersVector;
    r = filesParser.parse(configFile, parameters);

    configFile.close();
    return r;
}


size_t NsuConverterI::orderCreation = 0;
//patternsOfConverterNamesWithParameters[convertersQuantity] = {"mute [0-9]+ [0-9]+",
//                                                              "mix [0-9]+ [0-9]+ [$][0-9]+ [0-9]+"};
void NsuMute::parseParameters() {

}

void NsuMix::parseParameters() {

}

void NsuMute::convert() {

}

void NsuMix::convert() {

}
