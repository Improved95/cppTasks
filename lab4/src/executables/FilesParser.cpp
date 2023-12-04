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

const string NsuMute::parametersPattern = "([\\d]+[ ][\\d]+){1}";
int NsuMute::parseParameters() {
    int r;

    try {
        regex pattern(parametersPattern);
        if (!regex_match(this->parameters, pattern)) {
            throw IncorrectParametersFormatException(this->parameters);
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    cxxopts::Options options("converters parameters parser");
    options.add_options()
            ("begin", "Beggining second for mute.", cxxopts::value<int>())
            ("end", "Ending second for mute.", cxxopts::value<int>());
    options.parse_positional({"begin", "end"});

    cxxopts::ParseResult result;
    if ((r = fillUsingThreads(2, options, result)) != 0) {
        return r;
    }
    this->usingStream = pair(0, pair(result["begin"].as<int>(), result["end"].as<int>()));

    return r;
}

const string NsuMix::parametersPattern = "[\\d]+[\\s]{1}[\\d]+[\\s]{1}[$]{1}[\\d]+[\\s]{1}[\\d]+";
int NsuMix::parseParameters() {
    int r;

    try {
        regex pattern(parametersPattern);
        if (!regex_match(this->parameters, pattern)) {
            throw IncorrectParametersFormatException(this->parameters);
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    cxxopts::Options options("converters parameters parser");
    options.add_options()
            ("begin", "Begining second for mix.", cxxopts::value<int>())
            ("end", "Ending second for mix.", cxxopts::value<int>())
            ("input", "Input which will be mixed with.", cxxopts::value<string>())
            ("beginMixInput", "Second which will be mixed with.", cxxopts::value<int>());
    options.parse_positional({"begin", "end", "input", "beginMixInput"});

    cxxopts::ParseResult result;
    if ((r = fillUsingThreads(4, options, result)) != 0) {
        return r;
    }
    this->usingStream = pair(0, pair(result["begin"].as<int>(), result["end"].as<int>()));

    string referenceOnMixInputStr = result["input"].as<string>();
    size_t referenceOnMixInput = std::stoull(referenceOnMixInputStr.substr(1, referenceOnMixInputStr.size()));
    this->mixStream = pair(referenceOnMixInput, result["beginMixInput"].as<int>());

    return r;
}
