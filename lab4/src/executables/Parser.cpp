#include <iostream>
#include "Parser.h"
#include "Exceptions.h"
using std::string;
using std::vector;
using std::endl;
using std::cerr;

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char *argv[], string &config, string &output, vector<string> &inputs) {
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
            ("h,help", "Cout help list;", cxxopts::value<bool>()->default_value("false"))
            ("c,convert", "Execute converting;", cxxopts::value<bool>()->default_value("false"))
            ("ConfigFile", "Config file with parameters of converting;", cxxopts::value<string>())
            ("OutputFile", "Output file after converting;", cxxopts::value<string>())
            ("FilesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"ConfigFile", "OutputFile", "FilesForConverting"});
    options.positional_help("<config>.txt <output>.wav <input1>.wav [<input2>.wav ...]");

    try {
        if (argc < 2) {
            throw zeroArgumentException("Too few arguments entered.", &options);
        }
    } catch (zeroArgumentException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    }

    cxxopts::ParseResult result;
    try {
        result = options.parse(argc, argv);
    } catch (cxxopts::exceptions::exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    try {
        checkMutuallyArguments(result, options);
    } catch (MutuallyArgException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    }

    //check of existing config file and his correctness
    ParseFileNameWithAnyExtension parseFileNameWithAnyExtension;
    try {
        argumentIsExist("ConfigFile", result, options);
        parseFileNameWithAnyExtension.checkFileName(argv[2], result, options, "ConfigFile");
    } catch (ArgumentIsEntered &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    } catch (FileNameException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    }

    //check of existing output file and his correctness
    ParseFileNameWithSoundsExtension parseFileNameWithSoundsExtension;
    try {
        parseFileNameWithSoundsExtension.checkFileName(argv[3], result, options, "OutputFile");
    } catch (FileNameException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    } catch (ArgumentException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    }

    try {
        vector<string> inputFileNames = result["FilesForConverting"].as<vector<string>>();
        for (auto &el : inputFileNames) {
            parseFileNameWithSoundsExtension.checkFileName(el.c_str(), result, options, "FilesForConverting");
        }
    } catch (FileNameException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    } catch (ArgumentException &ex) {
        cerr << ex.sp_what() << endl;
        return ex.getErrorCode();
    }

    return 0;
}

void ParseConsoleArguments::checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option) {
    bool mutuallyArgumentIsExist = false;
    for (auto &el : mutuallyArguments) {
        if (result[el].count() > 0) {
            if (mutuallyArgumentIsExist) {
                throw MutuallyArgException("You input mulually arguments, choose correct mode.", &option);
            }
            mutuallyArgumentIsExist = true;
        }
    }
}

void ParseConsoleArguments::argumentIsExist(const char *optionName, cxxopts::ParseResult &result, cxxopts::Options &options) {
    if (result[optionName].count() < 1) {
        string message = "You didn't enter ";
        message.append(optionName);
        throw ArgumentIsEntered(message.c_str(), &options);
    }
}

void ParseFileNameWithAnyExtension::checkFileName(const char *fileName, const cxxopts::ParseResult &result,
                                                  const cxxopts::Options &options, const char *optionName) {

    regex regexPattern(this->namePattern + this->anyExtensionPattern);
    if (!regex_match(fileName, regexPattern)) {
        throw FileNameException("Incorrect filename", &options);
    }
}

void ParseFileNameWithSoundsExtension::checkFileName(const char *fileName, const cxxopts::ParseResult &result,
                                                     const cxxopts::Options &options, const char *optionName) {

    regex regexPattern(this->namePattern + this->anyExtensionPattern);
    for (auto el : this->soundExtensions) {
        regex regexPattern(this->namePattern + el);
        if (regex_match(fileName, regexPattern)) {
            return;
        }
    }
    throw FileNameException("Incorrect filename", &options);
}
