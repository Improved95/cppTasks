#include <regex>
#include <vector>
#include "FilesParser.h"
#include "Exceptions.h"
#include "Converter.h"
#include "ConvertersFactory.h"
using std::getline;
using std::regex;
using std::smatch;
using std::regex_search;
using std::vector;
using std::cerr;
using std::endl;

const string NsuConvertersInfo::ConvertersNamesPatterns = "^(\\w+)";
const string NsuConvertersInfo::convertersNames[convertersQuantity] = {"mute", "mix"};
const string NsuSoundProcessorConfigParser::parametersPattrerm = "[ ]([\\s\\S])+";

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

        regex pattern(NsuSoundProcessorConfigParser::parametersPattrerm);
        smatch match;
        regex_search(parameterStr, match, pattern);
        convertersVector.push_back(factory.create(nameConverter, ((string)match[0]).substr(1, ((string)match[0]).size())));
    }

    return 0;
}

string NsuSoundProcessorConfigParser::checkConverterName(string &parameterStr) {
    regex pattern(NsuConvertersInfo::getConvertersNamesPatterns());
    smatch match;
    for (size_t i = 0; i < NsuConvertersInfo::getConvertersQuantity(); i++) {
        auto el = NsuConvertersInfo::getConvertersName()[i];
        if (regex_search(parameterStr, match, pattern) && match[0] == el) {
            return (string)match[0];
        }
    }
    throw noExistConverterException((string)match[0]);
}
