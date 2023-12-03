#include <regex>
#include <vector>
#include "FilesParser.h"
#include "Exceptions.h"
#include "Converter.h"
#include "ConvertersFactory.h"
using std::getline;
using std::regex;
using std::smatch;
using std::vector;
using std::cerr;
using std::endl;

const string NsuConvertersInfo::ConvertersNamesPatterns = "^(\\w+)";
const string NsuConvertersInfo::convertersNames[convertersQuantity] = {"mute", "mix"};

int NsuSoundProcessorConfigParser::parse(ifstream &config, vector<NsuConverterI*> &convertersVector) {
    string parameterStr;
    NsuConvertersFactory factory;

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

        convertersVector.push_back(factory.create(nameConverter));
    }

    return 0;
}

string NsuSoundProcessorConfigParser::checkConverterName(string &parameterStr) {
    string nameConverter;
    regex pattern(NsuConvertersInfo::getConvertersNamesPatterns());
    smatch match;
    for (auto &el : *NsuConvertersInfo::getConvertersName()) {
        if (std::regex_search(parameterStr, match, pattern) && match[0] == el) {
            return (string)match[0];
        }
    }
    throw noExistConverterException((string)match[0]);
}
