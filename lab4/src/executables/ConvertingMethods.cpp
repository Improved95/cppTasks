#include <iostream>
#include "Converter.h"

char * BinaryStream::sampleBuffer = nullptr;
size_t NsuConverterI::secondNumber = 0;
int NsuMute::convert() {
    char *samplesInSecond;
    if (this->numberOfCreate == 0) {
        samplesInSecond = this->inputsVector[this->inputStreamInfo.first]->getNewSamplesInOneSecond();
    } else {
        samplesInSecond = this->inputsVector[this->inputStreamInfo.first]->getSampleBuffer();
    }

    if (secondNumber >= this->inputStreamInfo.second.first && secondNumber <= this->inputStreamInfo.second.second) {

    } else {
        this->convertingIsComplete = true;
    }

    if (this->numberOfCreate == orderCreation - 1) {
        size_t sampleRate = this->inputsVector[this->inputStreamInfo.first]->getHeader()->sampleRate;
        size_t bytePerSample = this->inputsVector[this->inputStreamInfo.first]->getHeader()->bytePerSample;
        this->output->pushInFile(samplesInSecond, sampleRate * bytePerSample);

        secondNumber++;
        if () {
            
        }
    } else {

    }

    return 0;
}

int NsuMix::convert() {
    return 0;
}
