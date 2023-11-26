#include <iostream>
#include <string>
#include "Parser.h"
#include "Exceptions.h"
#include "Messages.h"
#include "cxxopts.hpp"
#include "vector"
using std::string;
using std::vector;
using std::regex;
using std::regex_match;
using std::cout;
using std::endl;

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char **argv) {
    int r = 0;
    ArgumentsExceptions argumentsExceptions;
    ShowInfo showInfo;
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
        ("h,help", "Cout help list;")
        ("c,convert", "Execute converting.")
        ("configFile", "Config with rule of converting.", cxxopts::value<string>())
        ("filesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"configFile", "filesForConverting"});
    options.set_positional_help("config.txt output.wav input1.wav [input2.wav ...]");

    cxxopts::ParseResult result;
    if ((r = argumentsExceptions.cxxoptsParsingExceptionHandling(result, argc, argv, options)) != 0) {
        return r;
    }

    vector<size_t> argvs = {result.count("help"), result.count("convert")};
    if ((r = argumentsExceptions.mutuallyExclusiveArgHandling(argvs)) != 0) {
        return r;
    }

    if (result.count("help")) {
        cout << options.help() << endl;
        showInfo.coutConfigExample();
        return 0;
    }

    string configFileName = result["configFile"].as<string>();
    if ((r = argumentsExceptions.inputFileFormatIncorrectHandling(configFileName, (string)("[A-Za-z0-9]+[.]txt"), options)) != 0) {
        return r;
    }

    vector<string> inputFileNames = result["filesForConverting"].as<vector<string>>();
    if ((r = argumentsExceptions.inputFileFormatIncorrectHandling(configFileName, (string)("[A-Za-z0-9]+[.]wav"), options)) != 0) {
        return r;
    }

    return r;
}
