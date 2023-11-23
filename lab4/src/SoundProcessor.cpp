#include "SoundProcessor.h"

int SoundProcessor::convertWithConsoleParameters(int argc, char **argv) {
    ParseConsoleParameters parseConsoleParameters;
    return parseConsoleParameters.parseParametersAndInitialConvert(argc, argv);
}
