#include "SoundProcessor.h"
#include "ConsoleParser.h"
#include "Converter.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    int r;

    vector<string> arguments;
    r = parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv, arguments);
    if (r == -1) {
        return 0;
    } else if (r != 0) {
        return r;
    }

    NsuSoundProcessorManager nsuSoundProcessorManager;
    if ((r = nsuSoundProcessorManager.initializeConvertersAndInitialConvert(arguments)) != 0) {
        return r;
    }

    return r;
}
