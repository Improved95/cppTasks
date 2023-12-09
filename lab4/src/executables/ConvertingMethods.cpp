#include <iostream>
#include "Converter.h"

//char * BinaryStream::sampleBuffer = nullptr;

int NsuSoundProcessorManager::converting(vector<NsuConverterI*> &convertersVector) {
    int r;
//    this->output->getStream().close();
//    exit(-1);

    const size_t sampleRate = this->inputsVector[0]->getHeader()->sampleRate;
    const size_t bytePerSample = this->inputsVector[0]->getHeader()->bytePerSample;
    const size_t generalDataSize = this->inputsVector[0]->getHeader()->dataSize / bytePerSample;

    char *samplesBuffer = new char[sampleRate * bytePerSample];
    size_t readDataSize = 0;
    while(!this->convertingIsComplete) {
        for (auto &el : convertersVector) {
            if (el->createNumber == 0) {
                readDataSize = this->inputsVector[el->inputStreamInfo.first]->getNewSamplesInOneSecond(samplesBuffer);
                this->sampleNumber++;
            }

            if ((r = el->convert(samplesBuffer, readDataSize)) != 0) {
                delete samplesBuffer;
                return r;
            }

            if (el->createNumber == this->createNumber - 1) {
                this->output->pushInFile(samplesBuffer, readDataSize);
                if (this->sampleNumber >= generalDataSize) {
                    convertingIsComplete = true;
                }
            }
        }
    }

    delete samplesBuffer;
    return r;
}

int NsuMute::convert(char *samplesBuffer, const size_t bufferSize) {

    return 0;
}

int NsuMix::convert(char *samplesBuffer, const size_t bufferSize) {
    return 0;
}
