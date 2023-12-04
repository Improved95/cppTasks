#include "SoundProcessor.h"
#include "ConsoleParser.h"
#include "Converter.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    int r;

    vector<string> arguments = {"config.txt", "output.wav", "input.wav"};
//    if ((r = parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv, arguments)) != 0) {
//        return r;
//    }


    NsuSoundProcessorManager nsuSoundProcessorManager(arguments);
    if ((r = nsuSoundProcessorManager.convert()) != 0) {
        return r;
    }

    return r;
}
