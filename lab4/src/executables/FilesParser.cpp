#include <regex>
#include "FilesParser.h"
#include "Exceptions.h"
using std::getline;
using std::regex;
using std::smatch;
using std::cerr;
using std::endl;

const char* NsuSoundProcessorFilesParser::ConvertersNamesPatterns = "^(\\w+)";
const char* NsuSoundProcessorFilesParser::convertersNames[convertersQuantity] = {"mute", "mix"};

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
        regex pattern(ConvertersNamesPatterns);
        smatch match;
        bool converterIsExist = false;
        for (auto &el : convertersNames) {
            if (std::regex_search(parameterStr, match, pattern) && match[0] == el) {
                nameConverter = match[0];
                cerr << nameConverter << endl;
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

    auto it = NsuConverterParametersParserFactory::parametersParserRegistry.find(nameConverter)->second();
    it->parse(parameterStr);

    return 0;
}


const char* NsuSoundProcessorParametersParser::patternsOfConverterNamesWithParameters[convertersQuantity] = {"mute [0-9]+ [0-9]+",
                                                                                                             "mix [0-9]+ [0-9]+ [$][0-9]+ [0-9]+"};

int NsuMuteConverterParametersParser::parse(string &parameters) {
    try {
        cerr << "h1" << endl;
        cerr << parameters << endl;
        regex pattern(patternsOfConverterNamesWithParameters[0]);
        smatch match;
        if (regex_search(parameters, match, pattern) && match[0] != parameters) {
            throw IncorrectParametersFormatException(
                    concatenateTwoConstChar(concatenateStrAndChar("Incorrect format parameters in\"", match[0]), "\"."));
        }
        cerr << match[0] << endl;
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }


    return 0;
}

int NsuMixConverterParametersParser::parse(string &parameters) {
    return 0;
}

const unordered_map<string, function<ConverterParametersParser*()>> NsuConverterParametersParserFactory::parametersParserRegistry = {
        { NsuSoundProcessorFilesParser::getConvertersName()[0], []() { return new NsuMuteConverterParametersParser; } },
        { NsuSoundProcessorFilesParser::getConvertersName()[1], []() { return new NsuMixConverterParametersParser; } }
};
