#include "Exceptions.h"
#include "Messages.h"
#include <regex>
using std::cerr;
using std::endl;
using std::regex_match;
using std::regex;

void SoundProcessorExceptions::showMessageError(string message) {
    ShowError showError;
    showError.cerrError(message);
}

int ArgumentsExceptions::cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[]) {
    try {
        result = this->options.parse(argc, argv);
    } catch (const cxxopts::exceptions::exception &ex) {
        showMessageError(ex.what() + (string)("\n") + this->options.help());
        return returnErrorValue;
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
        showMessageError("You called mutually exclusive arguments." + (string)"\n" + this->options.help());
        return returnErrorValue;
    }
    return 0;
}

int ArgumentsExceptions::inputFileFormatIncorrectHandling(string &fileName, string pattern) {
    try {
        regex regexPattern(pattern);
        if (!regex_match(fileName, regexPattern)) {
            throw exception();
        }
    } catch(exception &ex) {
        showMessageError("Incorrect file name format." + (string)("\n") + this->options.help());
        return returnErrorValue;
    }
    return 0;
}

int ArgumentsExceptions::zeroArgumentExceptionHandling(int argc) {
    try {
        if (argc < 1) {
            throw exception();
        }
    } catch (exception &ex) {
        showMessageError("You input too few parameters. You should enter one option." + (string)("\n") + this->options.help());
        return returnErrorValue;
    }
    return 0;
}

int ArgumentsExceptions::requiredArgumentNonExistHandling(string option_, cxxopts::ParseResult &result) {
    try {
        if (result.count(option_) == 0) {
            throw exception();
        }
    } catch (exception &ex) {
        showMessageError("You didn't input " + option_ + (string)("\n") + this->options.help());
        return returnErrorValue;
    }
    return 0;
}
