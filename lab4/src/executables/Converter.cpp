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
    if ((r = NsuConverterI::createInputStreams(convertersVector, arguments)) != 0) { return r; }

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
int NsuConverterI::createInputStreams(vector<NsuConverterI*> &convertersVector, vector<string> &arguments) {
    int r;
    vector<bool> inputIsOpen(arguments.size(), false);

    for (auto &el : convertersVector) {
        if (inputIsOpen[el->usingStream.first + 2]) {
            continue;
        }
        BinaryStreamIn *temp = new BinaryStreamIn(arguments[el->usingStream.first + 2], r); // +2 потому что в аргументах первыми двумя лежат config и аутпут
        if (r != 0) { return r; }
        inputStreamsVector.push_back(temp);
        inputIsOpen[el->usingStream.first + 2] = true;
    }
    return r;
}

size_t NsuConverterI::positionConverting = 0;
void NsuMute::convert() {

}

void NsuMix::convert() {

}
