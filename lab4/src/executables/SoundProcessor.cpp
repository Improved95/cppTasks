#include "SoundProcessor.h"
#include "Parser.h"

int SoundProcessor::convertWithConsoleArguments(int argc, char **argv) {
    ParseConsoleArguments parseConsoleParameters;
    int r;

    string config, output;
    vector<string> inputs;
    if ((r = parseConsoleParameters.parseArgumentsAndInitialConvert(argc, argv, config, output, inputs)) != 0) {
        return r;
    }



    return r;
}
