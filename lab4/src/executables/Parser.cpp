#include <iostream>
#include <string>
#include <cstring>
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
    if ((r = argumentsExceptions.cxxoptsParsingExceptionHandling(result, argc, argv)) != 0) {
        return r;
    }

    if ((r = argumentsExceptions.zeroArgumentExceptionHandling(result.count("help") + result.count("convert")) != 0)) {
        return r;
    }

    //определяю взаимоисключающие параметры
    vector<size_t> argvs = {result.count("help"), result.count("convert")};
    if ((r = argumentsExceptions.mutuallyExclusiveArgHandling(argvs)) != 0) {
        return r;
    }

    if (result.count("help")) {
        cout << options.help() << endl;
        showInfo.coutInstruction();
        return 0;
    }

    FileNameExceptions fileNameExceptions(options);
    //Был ли введен конфиг
    if ((r = argumentsExceptions.requiredArgumentNonExistHandling("ConfigFile", result)) != 0) {
        return r;
    }
    string configFileName = result["ConfigFile"].as<string>();
    if ((r = fileNameExceptions.inputFileFormatIncorrectHandling(configFileName, ("[A-Za-z0-9]+[.]txt"))) != 0) {
        return r;
    }

    //Был ли введен выходной файл
    if ((r = argumentsExceptions.requiredArgumentNonExistHandling("OutputFile", result)) != 0) {
        return r;
    }
    configFileName = result["OutputFile"].as<string>();
    if ((r = fileNameExceptions.inputFileFormatIncorrectHandling(configFileName, ("[A-Za-z0-9]+[.]wav"))) != 0) {
        return r;
    }

    //Были ли введены файлы для конвертации
    if ((r = argumentsExceptions.requiredArgumentNonExistHandling("FilesForConverting", result)) != 0) {
        return r;
    }
    vector<string> inputFileNames = result["FilesForConverting"].as<vector<string>>();
    for (auto &el : inputFileNames) {
        if ((r = fileNameExceptions.inputFileFormatIncorrectHandling(el, ("[A-Za-z0-9]+[.]wav"))) != 0) {
            return r;
        }
    }



    return r;
}
