#include <regex>
#include "FilesParser.h"
#include "Converter.h"
#include "Streams.h"
using std::ifstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::convert() {
    int r;
    NsuSoundProcessorConfigParser filesParser;


    StreamIn configFile(arguments[0], r);
    if (r != 0) {
        return r;
    }

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector)) != 0) {
        return r;
    }
    if (convertersVector.size() == 0) {
        return 0;
    }

    for (auto &el : convertersVector) {
        if ((r = el->parseParameters()) != 0) {
            return r;
        }
    }

    /*while(!NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            el->convert();
        }
    }*/

    return r;
}

bool NsuConverterI::convertersIsOver(const vector<NsuConverterI*> &convertersVector) {
    bool converterIsOver = true;
    for (auto &el : convertersVector) {
        converterIsOver = el->convertingIsComplete;
    }
    return converterIsOver;
}

void NsuMute::convert() {

}

void NsuMix::convert() {

}
