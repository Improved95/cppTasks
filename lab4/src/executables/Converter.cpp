#include "FilesParser.h"
#include "Exceptions.h"
#include "Converter.h"
#include "Streams.h"
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

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector)) != 0) {
        return r;
    }

    ofstream fileOut;
    fileOut.open(arguments[1]);
    try {
        if (!fileOut.is_open()) {
            throw FileNotOpenException(arguments[1]);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        cerr << ex.getErrorCode() << endl;
    }

    StreamOut streamOut(&fileOut);
    while(NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            el->convert();
        }
    }

    configFile.close();
    return r;
}

bool NsuConverterI::convertersIsOver(const vector<NsuConverterI *> &convertersVector) {
    for (auto &el : convertersVector) {
        if (el->convertingIsComplete) {
            return true;
        }
    }
    return false;
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
