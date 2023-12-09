#include <iostream>
#include "Converter.h"

char * BinaryStream::sampleBuffer = nullptr;

int NsuMute::convert() {
    char *samplesInSecond;

    //если конвертер первый
    /*if (this->numberOfCreate == 0) {
        samplesInSecond = this->inputsVector[this->inputStreamInfo.first]->getNewSamplesInOneSecond();
        secondNumber++;
    } else {
        samplesInSecond = this->inputsVector[this->inputStreamInfo.first]->getSampleBuffer();
    }

    if (secondNumber >= this->inputStreamInfo.second.first && secondNumber <= this->inputStreamInfo.second.second) {

    }

    //если конвертер последний
    if (this->numberOfCreate == orderCreation - 1) {
        size_t sampleRate = this->inputsVector[this->inputStreamInfo.first]->getHeader()->sampleRate;
        size_t bytePerSample = this->inputsVector[this->inputStreamInfo.first]->getHeader()->bytePerSample;
        this->output->pushInFile(samplesInSecond, bytePerSample);
        t1 += 1;


        size_t dataSize = this->inputsVector[this->inputStreamInfo.first]->getHeader()->dataSize / bytePerSample;
        if (secondNumber >= dataSize) {
            convertingIsComplete = true;
        }
    } else {

    }*/

    return 0;
}

int NsuMix::convert() {
    return 0;
}
