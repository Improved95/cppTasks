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

int NsuSoundProcessorConfigParser::parse(ifstream &config, vector<string> &parameters, bool &stopReadingFile) {
    string parameterStr;
    if (!getline(config, parameterStr)) {
        stopReadingFile = true;
        return 0;
    }
    if (parameterStr[0] == '#') {
        getline(config, parameterStr);
    }

    string nameConverter;
    try {
        regex pattern(convertersNamesPattern);
        smatch match;
        bool converterIsExist = false;
        for (auto &el : convertersNames) {
            if (std::regex_search(parameterStr, match, pattern) && match[0] == el) {
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
        stopReadingFile = true;
        return ex.getErrorCode();
    }

    auto it = ConverterParametersParserFactory::parametersParserRegistry.find(nameConverter)->second();
    it->parse(parameterStr);

    return 0;
}

void MuteConverterParametersParser::parse(string &parameters) {
    cerr << parameters << endl;
}

void MixConverterParametersParser::parse(string &parameters) {

}

const unordered_map<string, function<ConverterParametersParser*()>> ConverterParametersParserFactory::parametersParserRegistry = {
        { FilesParser::getConvertersName()[0], []() { return new MuteConverterParametersParser; } },
        { FilesParser::getConvertersName()[1], []() { return new MixConverterParametersParser; } }
};
