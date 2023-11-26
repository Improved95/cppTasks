#include <iostream>
#include "Parser.h"
#include "Exceptions.h"
#include "cxxopts.hpp"
#include "vector"
using std::vector;
using std::regex;
using std::regex_match;
using std::cout;
using std::endl;

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char **argv) {
    int r = 0;
    ArgumentsExceptions argumentsExceptions;
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



    return r;
}
