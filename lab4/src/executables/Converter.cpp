#include <regex>
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

    for (auto &el : convertersVector) {
        if ((r = el->parseParameters()) != 0) {
            return r;
        }
    }
    exit(0);
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

void NsuMute::convert() {

}

void NsuMix::convert() {

}
