#include <iostream>
#include "Converter.h"

size_t NsuConverterI::secondNumber = 0;
int NsuMute::convert() {
    char *samplesInSecond;
    if (this->numberOfCreate == 0) {
        samplesInSecond = this->inputsVector[this->inputStreamInfo.first]->getNewSamplesInOneSecond();
    } else {
        samplesInSecond = this->output.
    }

    if (secondNumber >= this->inputStreamInfo.second.first && secondNumber <= this->inputStreamInfo.second.second) {

    }

    if (this->numberOfCreate == orderCreation - 1) {
        size_t sampleRate = this->inputsVector[this->inputStreamInfo.first]->getHeader()->sampleRate;
        size_t bytePerSample = this->inputsVector[this->inputStreamInfo.first]->getHeader()->bytePerSample;
        this->output->push(samplesInSecond, sampleRate * bytePerSample);
    } else {

    }

    return 0;
}

int NsuMix::convert() {
    return 0;
}
