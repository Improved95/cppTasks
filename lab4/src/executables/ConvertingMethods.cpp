#include <iostream>
#include "Converter.h"

int NsuSoundProcessorManager::converting(vector<NsuConverterI*> &convertersVector) {
    int r = 0;

    const size_t bytePerSample = this->inputsVector[0]->getHeader()->bytePerSample;
    const size_t generalSamplesNumber = this->inputsVector[0]->getHeader()->dataSize / bytePerSample;
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
                if (sampleNumber >= generalSamplesNumber) {
                    convertingIsComplete = true;
                }
                sampleNumber++;
            }
        }
    }

    return r;
}

void NsuMute::convert(Sample &sample, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {

    WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    if (sampleNumber >= this->inputStreamInfo.second.first * wavInfo->sampleRate
        && sampleNumber <= this->inputStreamInfo.second.second * wavInfo->sampleRate) {

        memset(sample.getData(), 0, sample.getSampleSize());

    }
}

void NsuMix::convert(Sample &sample, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {

    WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();

    if (sampleNumber >= this->inputStreamInfo.second.first * wavInfo->sampleRate
        && sampleNumber <= this->inputStreamInfo.second.second * wavInfo->sampleRate) {

        inputsVector[this->mixStream.first]->getSample(*(this->mixSample), this->currentMixSampleNumber);
        sample += *(this->mixSample);
        this->currentMixSampleNumber++;

    }
}

void Delay::convert(Sample &sample, const vector<BinaryStreamIn*> &inputsVector, 
                            const size_t sampleNumber) {
    WAVHeader *wavInfo = inputsVector[this->inputStreamInfo.first]->getHeader();

    

}
