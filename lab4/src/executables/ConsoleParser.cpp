#include <iostream>
#include "ConsoleParser.h"
#include "Exceptions.h"
using std::regex;
using std::regex_match;
using std::endl;
using std::cerr;

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char *argv[], vector<string> &arguments) {
    int r = 0;
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
            ("h,help", "Cout help list;", cxxopts::value<bool>()->default_value("false"))
            ("c,convert", "Execute converting;", cxxopts::value<bool>()->default_value("false"))
            ("ConfigFile", "Config file with parameters of converting;", cxxopts::value<string>())
            ("OutputFile", "Output file after converting;", cxxopts::value<string>())
            ("FilesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"ConfigFile", "OutputFile", "FilesForConverting"});
    options.positional_help("config.txt output.wav input1.wav [input2.wav ...]");

    try {
        if (argc < 2) {
            throw zeroArgumentException(&options);
        }
    } catch (zeroArgumentException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (cxxopts::exceptions::exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    string mode;
    try {
        mode = checkMutuallyArguments(result, options);
    } catch (MutuallyArgException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    if (mode == ParseConsoleArguments::mutuallyArguments[0]) {
        ShowInfo showInfo;
        showInfo.coutInstruction();
    } else if (mode == ParseConsoleArguments::mutuallyArguments[1]) {
        ParseArgumentsForNsuSoundProcessor parseArgumentsForNsuSoundProcessor;
        r = parseArgumentsForNsuSoundProcessor.parseFilesArguments(argv, result, options, arguments);
    }

    return r;
}

const string ParseConsoleArguments::mutuallyArguments[quantityModes] = {"help", "convert"};
int ParseArgumentsForNsuSoundProcessor::parseFilesArguments(char *argv[], cxxopts::ParseResult &result,
                                                            cxxopts::Options &options, vector<string> &arguments) {

    //check of existing config file and his correctness
    ParseFileNameWithAnyExtension parseFileNameWithAnyExtension;
    try {
        argumentIsExist("ConfigFile", result, options);
        parseFileNameWithAnyExtension.checkFileName(argv[2], options);
        arguments.push_back(argv[2]);
    } catch (ArgumentIsEntered &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    } catch (FileNameException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    //check of existing output file and his correctness
    ParseFileNameWithSoundsExtension parseFileNameWithSoundsExtension;
    try {
        argumentIsExist("OutputFile", result, options);
        parseFileNameWithSoundsExtension.checkFileName(argv[3], options);
        arguments.push_back(argv[3]);
    } catch (ArgumentIsEntered &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    } catch (FileNameException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    try {
        argumentIsExist("FilesForConverting", result, options);
        vector<string> inputFileNames = result["FilesForConverting"].as<vector<string>>();
        for (auto &el : inputFileNames) {
            parseFileNameWithSoundsExtension.checkFileName(el.c_str(), options);
            arguments.push_back(el);
        }
    } catch (ArgumentIsEntered &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    } catch (FileNameException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    return 0;
}

string ParseConsoleArguments::checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option) {
    bool mutuallyArgumentIsExist = false;
    string returnMode;
    for (auto &el : mutuallyArguments) {
        if (result[el].count() > 0) {
            if (mutuallyArgumentIsExist) {
                throw MutuallyArgException("You input mutually arguments, choose correct mode.", &option);
            }
            returnMode = el;
            mutuallyArgumentIsExist = true;
        }
        if (result[el].count() > 1) {
            throw MutuallyArgException("You input so many same arguments.", &option);
        }
    }
    return returnMode;
}

void ParseConsoleArguments::argumentIsExist(const string &optionName, cxxopts::ParseResult &result, cxxopts::Options &options) {
    if (result[optionName].count() < 1) {
        throw ArgumentIsEntered(optionName, &options);
    }
}

const string ParseFileName::namePattern = "(\\w+)";
const string ParseFileName::anyExtensionPattern = "([.](\\w)+)*";
void ParseFileNameWithAnyExtension::checkFileName(const string &fileName, const cxxopts::Options &options) {
    regex pattern(this->namePattern + this->anyExtensionPattern);
    if (!regex_match(fileName, pattern)) {
        throw FileNameException(fileName, &options);
    }
}

const string ParseFileNameWithSoundsExtension::soundExtensions[quantitySoundExtensions] = {"[.]wav"};
void ParseFileNameWithSoundsExtension::checkFileName(const string &fileName, const cxxopts::Options &options) {
    for (auto &el : this->soundExtensions) {
        regex pattern(this->namePattern + el);
        if (regex_match(fileName, pattern)) {
            return;
        }
    }
    throw FileNameException(fileName, &options);
}
