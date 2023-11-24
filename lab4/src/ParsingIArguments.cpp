#include "SoundProcessor.h"
#include <regex>
#include <vector>
using std::regex;
using std::regex_match;
using std::vector;

int ParseConsoleArguments::parseConfigFileName(char *argv[]) {
    CoutMessages coutMessages;
    std::regex pattern("[A-Za-z0-9]+[.]txt");
    if (!regex_match(argv[2], pattern)) {
        coutMessages.coutError("Incorrect name of file config.");
        return 1;
    }
    ifstream configFile;
    configFile.open(argv[2]);
    if (!configFile.is_open()) {
        coutMessages.coutError("Cannot open config file.");
        return 1;
    }
    return 0;
}

int ParseConsoleArguments::parseWavFilesName(int argc, char *argv[]) {
    CoutMessages coutMessages;
    std::regex pattern("[A-Za-z0-9]+[.]txt");
    vector<ifstream> streamVector;
    for (size_t i = 3; i < argc; i++) {
        if (!regex_match(argv[i], pattern)) {
            coutMessages.coutError("Incorrect name of WAV file.");
            return 1;
        }
        ifstream wavFile;
        wavFile.open(argv[i]);
        if (!wavFile.is_open()) {
            string mes = "Cannot open" + std::to_string(i - 2) + "wav file.";
            coutMessages.coutError(mes);
        }
        streamVector.push_back(wavFile);
    }
    return 0;
}

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char **argv) {
    int r;
    CoutMessages coutMessages;
    if (argc < 2) {
        coutMessages.coutErrorAndHelp("Incorrect console arguments.");
        return 1;
    }
    if (argv[1] == "-h") {
        coutMessages.coutHelp();
        return 0;
    } else if (argv[1] == "-c") {
        if ((r = parseConfigFileName(argv)) != 0) {
            return r;
        }
        if ((r = parseWavFilesName(argc, argv)) != 0) {
            return r;
        }
     } else {
        coutMessages.coutErrorAndHelp("Incorrect console arguments.");
        return 1;
    }

    return r;
}
