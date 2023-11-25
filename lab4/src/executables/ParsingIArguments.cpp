#include "SoundProcessor.h"
#include "Converter.h"
#include <regex>
using std::regex;
using std::regex_match;

int ParseConsoleArguments::parseConfigFileArg(char **argv, vector<OpenFilesSmartPointers> &openedFilesVector) {
    CoutMessages coutMessages;
    regex patternConfigName("[A-Za-z0-9]+[.]txt");
    if (!regex_match(argv[2], patternConfigName)) {
        coutMessages.coutError("Incorrect name of file config.");
        return 1;
    }
    fstream configFile;
    configFile.open(argv[2], fstream::in);
    OpenFilesSmartPointers openedFile(&configFile);
    if (!configFile.is_open()) {
        coutMessages.coutError("Cannot open config file.");
        return 2;
    }
    openedFilesVector.push_back(openedFile);
    return 0;
}

int ParseConsoleArguments::parseWavFilesArg(int argc, char **argv, vector<OpenFilesSmartPointers> &openedFilesVector) {
    CoutMessages coutMessages;
    regex patternWavFilesName("[A-Za-z0-9]+[.]wav");
    for (size_t i = 3; i < size_t(argc + 1); i++) {
        if (!regex_match(argv[i], patternWavFilesName)) {
            coutMessages.coutError("Incorrect name of WAV file.");
            return 1;
        }
        fstream wavFile;
        wavFile.open(argv[i], fstream::in);
        OpenFilesSmartPointers openedFile(&wavFile);
        if (!wavFile.is_open()) {
            string mes = "Cannot open" + std::to_string(i - 2) + "wav file.";
            coutMessages.coutError(mes);
            return 2;
        }
        openedFilesVector.push_back(openedFile);
    }
    ConverterManager converterManager;
    converterManager.initialConverterManager();
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
        vector<OpenFilesSmartPointers> openedFilesVector;
        if ((r = parseConfigFileArg(argv, openedFilesVector)) != 0) {
            return r;
        }
        if ((r = parseWavFilesArg(argc, argv, openedFilesVector)) != 0) {
            return r;
        }
     } else {
        coutMessages.coutErrorAndHelp("Incorrect console arguments.");
        return 1;
    }

    return r;
}
