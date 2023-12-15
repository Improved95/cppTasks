#include <iostream>
#include "Converter.h"

int NsuSoundProcessorManager::converting(vector<NsuConverterI*> &convertersVector) {
    int r = 0;

    const size_t sampleRate = this->inputsVector[0]->getHeader()->sampleRate;
    const size_t bytePerSample = this->inputsVector[0]->getHeader()->bytePerSample;
    const size_t generalTime = this->inputsVector[0]->getHeader()->dataSize / (bytePerSample * sampleRate);
    char *samplesBuffer = new char[sampleRate * bytePerSample];
    size_t secondNumber = 0;
    size_t readDataSize = 0;
    bool convertingIsComplete = false;

    while(!convertingIsComplete) {
        for (auto &el : convertersVector) {
            if (el->createNumber == 0) {
                readDataSize = this->inputsVector[el->inputStreamInfo.first]->getNewSamplesInOneSecond(samplesBuffer, secondNumber);
            }

            el->convert(samplesBuffer, readDataSize, this->inputsVector, secondNumber);

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

void NsuMute::convert(char *samplesBuffer, const size_t inputBufferSize, const vector<BinaryStreamIn*> &, const size_t secondNumber) {
    if (secondNumber >= this->inputStreamInfo.second.first && secondNumber <= this->inputStreamInfo.second.second) {

        memset(samplesBuffer, 0, inputBufferSize);

    }
}

void NsuMix::convert(char *samplesBuffer, const size_t inputBufferSize, const vector<BinaryStreamIn*> &inputsVector, const size_t secondNumber) {
    static size_t currentMixSecond = 0;
    static char *mixStreamBuffer = new char[inputsVector[this->mixStream.first]->getHeader()->sampleRate
                                            * inputsVector[this->mixStream.first]->getHeader()->bytePerSample];
    size_t readDataSize = inputsVector[this->mixStream.first]->getNewSamplesInOneSecond(mixStreamBuffer,
                                                                                        this->mixStream.second + currentMixSecond);

    if (secondNumber >= this->inputStreamInfo.second.first && secondNumber <= this->inputStreamInfo.second.second) {

        for (size_t i = 0; i < inputBufferSize && i < readDataSize; i += 2) {
//            size_t tempSample = (samplesBuffer[i] + mixStreamBuffer[i]) / 2;
//            samplesBuffer[i] = (char)tempSample;

            /*short int firstByte = samplesBuffer[i];
            short int secondByte = samplesBuffer[i + 1];
            short int combinedShort = (secondByte << 8) | firstByte;

            unsigned char resultBytes[2];
            resultBytes[0] = combinedShort & 0xFF;        // Младший байт
            resultBytes[1] = (combinedShort >> 8) & 0xFF; // Старший байт

            samplesBuffer[i] = resultBytes[0];
            resultBytes[1]*/

            char s1[2];
            memset(s1, samplesBuffer[i], 1);
            memset(s1, samplesBuffer[i] + 1, 1);

            char s2[2];
            memset(s1, mixStreamBuffer[i], 1);
            memset(s1, mixStreamBuffer[i] + 1, 1);

            short int s1i, s2i;
            s1i = *reinterpret_cast<short int*>(s1);
            s2i = *reinterpret_cast<short int*>(s2);



            size_t tempSample = s1i + s2i;
            memset(samplesBuffer + i, (short int)tempSample, 2);
        }

    }
    currentMixSecond++;
}

void Delay::convert(char *samplesBuffer, const size_t inputBufferSize, const vector<BinaryStreamIn*> &inputsVector, const size_t secondNumber) {
    static WAVHeader *inputInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    static char *delaySamplesBuffer = new char[(inputInfo->bytePerSample * inputInfo->sampleRate) *
                                               (this->feedBack * (this->timeOfDelay + temp) / 1000 + 2)];
    static size_t indexOfsamplesNumbersOfEcho = 0;

    // fill mix buffer
    if (secondNumber - ((this->timeOfDelay + this->temp) / 1000) >= this->inputStreamInfo.second.first &&
    secondNumber + ((this->timeOfDelay + this->temp) / 1000) <= this->inputStreamInfo.second.second) {

        static size_t delaySampleIndex = 0;
        for (; delaySampleIndex < inputBufferSize; delaySampleIndex++) {

        }

    }

    //mixing
    if (secondNumber >= this->inputStreamInfo.second.first &&
        secondNumber <= this->inputStreamInfo.second.second) {

        for (size_t i = 0; i < inputBufferSize; i++) {
            for (size_t j = 0; j < this->echosInfo.size(); j++) {
                size_t tempSample = samplesBuffer[j] + 1;
            }
        }
    }
}
