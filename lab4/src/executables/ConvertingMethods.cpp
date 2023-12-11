#include <iostream>
#include "Converter.h"

//char * BinaryStream::sampleBuffer = nullptr;

int NsuSoundProcessorManager::converting(vector<NsuConverterI*> &convertersVector) {
    int r = 0;

    const size_t sampleRate = this->inputsVector[0]->getHeader()->sampleRate;
    const size_t bytePerSample = this->inputsVector[0]->getHeader()->bytePerSample;
    const size_t generalTime = this->inputsVector[0]->getHeader()->dataSize / (bytePerSample * sampleRate);
    char *samplesBuffer = new char[sampleRate * bytePerSample];
    size_t secondNumber = 0;
    size_t readDataSize = 0;

    while(!this->convertingIsComplete) {
        for (auto &el : convertersVector) {
            if (el->createNumber == 0) {
                readDataSize = this->inputsVector[el->inputStreamInfo.first]->getNewSamplesInOneSecond(samplesBuffer, secondNumber);
            }

            if (secondNumber >= el->inputStreamInfo.second.first && secondNumber <= el->inputStreamInfo.second.second) {
                el->convert(samplesBuffer, readDataSize, this->inputsVector);
            }

            if (el->createNumber == this->createNumber - 1) {
                this->output->pushInFile(samplesBuffer, readDataSize);
                if (secondNumber >= generalTime) {
                    convertingIsComplete = true;
                }
                secondNumber++;
            }
        }
    }

    delete[] samplesBuffer;
    return r;
}

void NsuMute::convert(char *samplesBuffer, const size_t bufferSize, const vector<BinaryStreamIn*> &) {
        memset(samplesBuffer, 0, bufferSize);
}

void NsuMix::convert(char *samplesBuffer, const size_t bufferSize, const vector<BinaryStreamIn*> &inputsVector) {
    size_t readDataSize = inputsVector[this->mixStream.first]->getNewSamplesInOneSecond(this->mixStreamBuffer,
                                                                                        this->mixStream.second + this->currentSecond);

    for(size_t i = 0; i < bufferSize && i < readDataSize; i++) {
        size_t tempSample = (samplesBuffer[i] + this->mixStreamBuffer[i]) / 2;
        samplesBuffer[i] = (char)tempSample;
    }

    this->currentSecond++;
}
