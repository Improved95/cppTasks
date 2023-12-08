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
using std::regex_match;
using std::istringstream;

const string NsuConvertersInfo::ConvertersNamesPatterns = "^(\\w+)";
const string NsuConvertersInfo::convertersNames[convertersQuantity] = {"mute", "mix"};
const string NsuSoundProcessorConfigParser::parametersPattrerm = "[ ]([\\s\\S])+";

int NsuSoundProcessorConfigParser::parse(StreamIn &config, vector<NsuConverterI*> &convertersVector) {
    string parameterStr;
    NsuConvertersFactory factory;

    while (getline(config.getStream(), parameterStr)) {
        if (parameterStr[0] == '#' || parameterStr == "") {
            if (!getline(config.getStream(), parameterStr)) {
                return 0;
            };
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
    const size_t parametersQuantity = 2;
    if ((r = fillUsingThreads(parametersQuantity, options, result)) != 0) {
        return r;
    }
    this->usingStream = pair(0, pair(result["begin"].as<int>(), result["end"].as<int>()));

    return r;
}

const string NsuMix::parametersPattern = "[\\d]+[\\s]{1}[\\d]+[\\s]{1}-i[\\s]{1}[\\d]+[\\s]{1}[\\d]+";
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
            ("begin", "Begining second for mix.", cxxopts::value<size_t>())
            ("end", "Ending second for mix.", cxxopts::value<size_t>())
            ("i,input", "Number of input which will be mixed with.", cxxopts::value<size_t>())
            ("beginInMixInput", "Second in input which will be mixed with.", cxxopts::value<size_t>());
    options.parse_positional({"begin", "end", "input", "beginInMixInput"});

    cxxopts::ParseResult result;
    const size_t parametersQuantity = 5;
    if ((r = fillUsingThreads(parametersQuantity, options, result)) != 0) {
        return r;
    }

    this->usingStream = pair(0, pair(result["begin"].as<size_t>(), result["end"].as<size_t>()));        // самый первый аргумент - индекс в векторе инпутов
    this->mixStream = pair(result["input"].as<size_t>() - 1, result["beginInMixInput"].as<size_t>());   // то же самое

    return r;
}

size_t NsuConverterI::orderCreation = 0;
int NsuConverterI::fillUsingThreads(const size_t parametersQuantity,
                                    cxxopts::Options &options, cxxopts::ParseResult &result) {
    istringstream iss(this->parameters);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
//    const char** charArray = new const char*[parametersQuantity + 1];
/*написать проверку для массива в куче и использовать его, или все равно...*/
    const char* charArray[10];
    for (size_t i = 0; i < words.size(); i++) {
        charArray[i + 1] = words[i].c_str();
    }

    try {
        result = options.parse(parametersQuantity + 1, charArray);
    } catch (cxxopts::exceptions::exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    return 0;
}

int NsuConverterI::checkParameters() {
    try {
        if (this->usingStream.second.first > this->usingStream.second.second) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
    try {
        if (this->usingStream.second.second > (this->wavInfo->dataSize / this->wavInfo->frequency / this->wavInfo->bytePerSample)) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders, you out from file border.");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
}

int NsuMute::checkUniqueParameters() {
    return 0;
}

int NsuMix::checkUniqueParameters() {
    try {
        if (this->mixStream.second >
            (this->wavInfo->dataSize / this->wavInfo->frequency / this->wavInfo->bytePerSample)) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders, you out from file border.");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }



}
