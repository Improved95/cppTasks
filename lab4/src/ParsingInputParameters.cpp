#include "SoundProcessor.h"

int ParseConsoleParameters::parseParametersAndInitialConvert(int argc, char **argv) {
    CoutMessages coutMessages;
    if (argc < 2) {
        coutMessages.coutErrorAndHelp("Incorrect console parameters.");
        return 1;
    }
    if (argv[1] == "-h") {
        coutMessages.coutHelp();
        return 0;
    } else if (argv[1] == "-c") {

    } else {
        coutMessages.coutErrorAndHelp("Incorrect console parameters.");
        return 1;
    }

    return 0;
}

