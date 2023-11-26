#include "SoundProcessor.h"
using std::regex;
using std::regex_match;

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char **argv) {
    int r = 0;
    CoutMessages coutMessages;
    ParsersExceptions parsersExceptions;
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
        ("h,help", "Cout help list;")
        ("c,convert", "Execute converting.")
        ("configFile", "Config with rule of converting.", cxxopts::value<string>())
        ("filesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"configFile", "filesForConverting"});
    options.set_positional_help("config.txt output.wav input1.wav [input2.wav ...]");

    cxxopts::ParseResult result;
    if ((r = parsersExceptions.cxxoptsParsingExceptionHandling(result, argc, argv, options)) != 0) {
        cout << "work" << endl;
        return r;
    }

    if (result.count("help") && result.count("convert")) {
        cout << options.help() << endl;
        coutMessages.coutConfigExample();
        return 1;
    }

    return r;
}
