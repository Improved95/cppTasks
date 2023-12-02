#include <regex>
#include "FilesParser.h"
#include "Exceptions.h"
using std::getline;
using std::regex;
using std::smatch;
using std::cerr;
using std::endl;

const string NsuSoundProcessorFilesParser::ConvertersNamesPatterns = "^(\\w+)";
const string NsuSoundProcessorFilesParser::convertersNames[convertersQuantity] = {"mute", "mix"};

int NsuSoundProcessorConfigParser::parse(ifstream &config, vector<string> &parameters) {
    string parameterStr;
    while (getline(config, parameterStr)) {
        if (parameterStr[0] == '#') {
            getline(config, parameterStr);
        }

        string nameConverter;
        try {
            nameConverter = checkConverterName(parameterStr);
        } catch (noExistConverterException &ex) {
            cerr << ex.ex_what() << endl;
            return ex.getErrorCode();
        }


    }


    return 0;
}

string NsuSoundProcessorConfigParser::checkConverterName(string &parameterStr) {
    string nameConverter;
    regex pattern(ConvertersNamesPatterns);
    smatch match;
    for (auto &el : convertersNames) {
        if (std::regex_search(parameterStr, match, pattern) && match[0] == el) {
            return (string)match[0];
        }
    }
    throw noExistConverterException((string)match[0]);
}

//patternsOfConverterNamesWithParameters[convertersQuantity] = {"mute [0-9]+ [0-9]+",
//                                                              "mix [0-9]+ [0-9]+ [$][0-9]+ [0-9]+"};


