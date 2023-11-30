#include "SoundProcessor.h"
#include "ConsoleParser.h"
#include "Converter.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    int r;

    vector<string> arguments;
    if ((r = parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv, arguments)) != 0) {
        return r;
    }

    NsuSoundProcessorManager nsuSoundProcessorManager(arguments);
    nsuSoundProcessorManager.convert();

    return r;
}
