#include <iostream>
#include "Converter.h"

int NsuSoundProcessorManager::converting(vector<NsuConverterI*> &convertersVector) {
    int r = 0;

    const size_t bytePerSample = this->inputsVector[0]->getHeader()->bytePerSample;
    const size_t generalTime = this->inputsVector[0]->getHeader()->dataSize / bytePerSample;
    Sample sample(bytePerSample);
    size_t sampleNumber = 0;
    bool convertingIsComplete = false;

    while(!convertingIsComplete) {
        for (auto &el : convertersVector) {
            if (el->createNumber == 0) {
                this->inputsVector[el->inputStreamInfo.first]->getSample(sample);
            }

            el->convert(sample, this->inputsVector, sampleNumber);

            if (el->createNumber == this->createNumber - 1) {
                this->output->pushInFile(sample.getData(), sample.getSampleSize());
                if (sampleNumber >= generalTime) {
                    convertingIsComplete = true;
                }
                sampleNumber++;
            }
        }
    }

    return r;
}

void NsuMute::convert(Sample &temp, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {

    static WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    if (sampleNumber >= this->inputStreamInfo.second.first * wavInfo->sampleRate
        && sampleNumber <= this->inputStreamInfo.second.second * wavInfo->sampleRate) {

        memset(temp.getData(), 0, temp.getSampleSize());

    }
}

void NsuMix::convert(Sample &temp, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {

    static WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    // size_t readDataSize = inputsVector[this->mixStream.first]->getNewSamplesInOneSecond(this->mixStreamBuffer,
                                                                                        // this->mixStream.second + this->currentMixSecond);

    if (sampleNumber >= this->inputStreamInfo.second.first * wavInfo->sampleRate
        && sampleNumber <= this->inputStreamInfo.second.second * wavInfo->sampleRate) {

        // size_t tempSample = (samplesBuffer[i] + this->mixStreamBuffer[i]) / 2;
        // samplesBuffer[i] = (char) tempSample;

    }
    this->currentMixSecond++;
}

void Delay::convert(Sample &temp, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {
    static WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    static size_t indexOfsamplesNumbersOfEcho = 0;

    // fill mix buffer
    // if (secondNumber - ((this->timeOfOneEcho + this->temp) / 1000) >= this->inputStreamInfo.second.first &&
    //     secondNumber + ((this->timeOfOneEcho + this->temp) / 1000) <= this->inputStreamInfo.second.second) {

    //     static size_t delaySampleIndex = 0;
    //     for (; delaySampleIndex < inputBufferSize; delaySampleIndex++) {

    //     }

    // }

    //mixing
    // if (secondNumber >= this->inputStreamInfo.second.first &&
    //     secondNumber <= this->inputStreamInfo.second.second) {

    //     for (size_t i = 0; i < inputBufferSize; i++) {
    //         for (size_t j = 0; j < this->echosInfo.size(); j++) {
    //             size_t tempSample = samplesBuffer[j] + 1;
    //         }
    //     }
    // }
}
