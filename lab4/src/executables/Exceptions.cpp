#include <iostream>
#include "Exceptions.h"
#include "Messages.h"
#include "cxxopts.hpp"
#include <string>
using std::regex;
using std::regex_match;
using std::cerr;
using std::endl;

void SoundProcessorExceptions::showMessageError(string message) {
    ShowError showError;
    showError.cerrError(message);
}

int ArgumentsExceptions::cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[], cxxopts::Options options) {
    try {
        result = options.parse(argc, argv);
    } catch (exception &ex) {
        showMessageError(ex.what() + (string)("\n") + options.help());
        return 1;
    }
    return 0;
}

int ArgumentsExceptions::mutuallyExclusiveArgHandling(vector<size_t> &argvs) {
    try {
        size_t saveEl = argvs[0];
        for (size_t i = 1; i < argvs.size(); i++) {
            if (saveEl == argvs[i]) {
                throw exception();
            }
        }
    } catch (exception &ex) {
        showMessageError("You called mutually exclusive arguments.");
        return 1;
    }
    return 0;
}

int ArgumentsExceptions::inputFileFormatIncorrectHandling(string &string, ) {
    try {

    } catch(exception &ex) {

    }
    return 0;
}
