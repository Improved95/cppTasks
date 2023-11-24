#include "../headers/SoundProcessor.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    return parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv);
}

