#include <regex>
#include "FilesParser.h"
#include "Exceptions.h"
using std::getline;
using std::regex;
using std::smatch;
using std::cerr;
using std::endl;

const char* FilesParser::convertersNamesPattern = "^(\\w+)";
const char* FilesParser::convertersNames[quantityConverter] = {"mute", "mix"};

int NsuSoundProcessorConfigParser::parse(ifstream &config, vector<string> &parameters) {
    string parameter;
    if (!getline(config, parameter)) {
        return -1;
    }
    if (parameter[0] == '#') {
        return 0;
    }

    string nameConverter;
    try {
        regex pattern(convertersNamesPattern);
        smatch match;
        bool converterIsExist = false;
        for (auto &el : convertersNames) {
            if (std::regex_search(parameter, match, pattern) && match[0] == el) {
                nameConverter = match[0];
                converterIsExist = true;
                break;
            }
        }
        if (!converterIsExist) {
            throw noExistConverterException(
                    concatenateTwoConstChar(concatenateStrAndChar("Converter \'", match[0]), "\" does not exist."));
        }
    } catch (noExistConverterException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    auto it = ConverterParametersParserFactory::parametersParserRegistry.find(nameConverter)->second();

    string test;
    it->parse(test);

    return 0;
}

void MuteConverterParametersParser::parse(string &parameters) {

}

void MixConverterParametersParser::parse(string &parameters) {

}

const unordered_map<string, function<ConverterParametersParser*()>> ConverterParametersParserFactory::parametersParserRegistry = {
        { FilesParser::getConvertersName()[0], []() { return new MuteConverterParametersParser; } }
};
