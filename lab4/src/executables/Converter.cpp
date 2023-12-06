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
    if (r != 0) { return r; }

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector)) != 0) { return r; }
    if (convertersVector.size() == 0) { return 0; }

    for (auto &el : convertersVector) {
        if ((r = el->parseParameters()) != 0) { return r; }
    }

    if ((r = NsuConverterI::createInputStreams(arguments)) != 0) { return r; }

    /*while(!NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            el->convert();
        }
    }*/

    return r;
}

bool NsuConverterI::convertersIsOver(const vector<NsuConverterI*> &convertersVector) {
    for (auto &el : convertersVector) {
        if (!el->convertingIsComplete) {
            return false;
        }
    }
    return true;
}

vector<BinaryStreamIn*> NsuConverterI::inputStreamsVector = {};
int NsuConverterI::createInputStreams(vector<string> &fileNamesVector) {
    int r;
    for (auto el = fileNamesVector.begin() + 2; el != fileNamesVector.end(); el++) {
        BinaryStreamIn *temp = new BinaryStreamIn(*el, r);
        if (r != 0) { return r; }
        inputStreamsVector.push_back(temp);
    }
    return r;
}

void NsuMute::convert() {

}

void NsuMix::convert() {

}
