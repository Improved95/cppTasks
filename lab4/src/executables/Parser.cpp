#include <iostream>
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

int ParseConsoleArguments::parseArgumentsAndInitialConvert(int argc, char *argv[], string &config, string &output, vector<string> &inputs) {
    /*
    int r;
    ShowInfo showInfo;
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
        ("h,help", "Cout help list;")
        ("c,convert", "Execute converting;")
        ("ConfigFile", "Config file with parameters of converting;", cxxopts::value<string>())
        ("OutputFile", "Output file after converting;", cxxopts::value<string>())
        ("FilesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"ConfigFile", "OutputFile", "FilesForConverting"});
    options.positional_help("<config>.txt <output>.wav <input1>.wav [<input2>.wav ...]");

    ArgumentsExceptions argumentsExceptions(options);

    cxxopts::ParseResult result;
    if ((r = argumentsExceptions.checkCxxoptsParsing(result, argc, argv)) != 0) {
        return r;
    }

    if ((r = argumentsExceptions.checkZeroArguments(result.count("help") + result.count("convert")) != 0)) {
        return r;
    }

    //определяю взаимоисключающие параметры
    vector<size_t> argvs = {result.count("help"), result.count("convert")};
    if ((r = argumentsExceptions.checkMutuallyExclusiveArg(argvs)) != 0) {
        return r;
    }

    if (result.count("help")) {
        cout << options.help() << endl;
        showInfo.coutInstruction();
        return 0;
    }

    FileNameWithDiffExtentionsExceptions fileNameWithDiffEE(options);
    //Был ли введен конфиг
    if ((r = argumentsExceptions.checkRequiredArgument("ConfigFile", result)) != 0) {
        return r;
    }
    string fileName = result["ConfigFile"].as<string>();
    if ((r = fileNameWithDiffEE.checkTxtFileName(fileName)) != 0) {
        return r;
    }

    //Был ли введен выходной файл
    if ((r = argumentsExceptions.checkRequiredArgument("OutputFile", result)) != 0) {
        return r;
    }
    fileName = result["OutputFile"].as<string>();
    if ((r = fileNameWithDiffEE.checkInputFileWithDiffFormat(fileName)) != 0) {
        return r;
    }

    //Были ли введены файлы для конвертации
    if ((r = argumentsExceptions.checkRequiredArgument("FilesForConverting", result)) != 0) {
        return r;
    }
    vector<string> inputFileNames = result["FilesForConverting"].as<vector<string>>();
    for (auto &el : inputFileNames) {
        if ((r = fileNameWithDiffEE.checkInputFileWithDiffFormat(el)) != 0) {
            return r;
        }
    }

    return r;
    */

    int r = 0;
    cxxopts::Options options("./SoundProcessor", "Converting streams with input parameteres.");

    options.add_options()
            ("h,help", "Cout help list;")
            ("c,convert", "Execute converting;")
            ("ConfigFile", "Config file with parameters of converting;", cxxopts::value<string>())
            ("OutputFile", "Output file after converting;", cxxopts::value<string>())
            ("FilesForConverting", "Input files for converting.", cxxopts::value<vector<string>>());
    options.parse_positional({"ConfigFile", "OutputFile", "FilesForConverting"});
    options.positional_help("<config>.txt <output>.wav <input1>.wav [<input2>.wav ...]");

    cxxopts::ParseResult result;

    try {
        result = options.parse(argc, argv);
    } catch (ArgumentException &ex) {
        cerr << ex.what() << endl;
        cout << "h1" << endl;
    }



    return 0;
}
