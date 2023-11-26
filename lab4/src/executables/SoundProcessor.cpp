#include "SoundProcessor.h"
#include "Parser.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    return parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv);
}
