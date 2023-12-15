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
const string NsuConvertersInfo::convertersNames[convertersQuantity] = {"mute", "mix", "delay"};
const string NsuSoundProcessorConfigParser::parametersPattrerm = "[ ]([\\s\\S])+";

int NsuSoundProcessorConfigParser::parse(StreamIn &config, vector<NsuConverterI*> &convertersVector, size_t &numberCreate) {
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
        convertersVector.push_back(factory.create(nameConverter, ((string)match[0]).substr(1, ((string)match[0]).size()), numberCreate));
        numberCreate++;
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

int NsuMute::parseParameters() {
    int r;
    const string parametersPattern = "([\\d]+[ ][\\d]+){1}";

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
    if ((r = getParseResult(parametersQuantity, options, result)) != 0) {
        return r;
    }
    this->inputStreamInfo = pair(0, pair(result["begin"].as<int>(), result["end"].as<int>()));

    return r;
}

int NsuMix::parseParameters() {
    int r;
    const string parametersPattern = "[\\d]+[\\s]{1}[\\d]+[\\s]{1}-i[\\s]{1}[\\d]+[\\s]{1}[\\d]+";

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
    if ((r = getParseResult(parametersQuantity, options, result)) != 0) {
        return r;
    }

    this->inputStreamInfo = pair(0, pair(result["begin"].as<size_t>(), result["end"].as<size_t>()));
    this->mixStream = pair(result["input"].as<size_t>() - 1, result["beginInMixInput"].as<size_t>());

    return r;
}

int Delay::parseParameters() {
    int r;
    const string parametersPattern = "[\\d]+[\\s]{1}[\\d]+[\\s]{1}[\\d]+[\\s]{1}[\\d]+[\\s]{1}[\\d]+[\\s]{1}[\\d]+";

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
            ("begin", "Begining second for delay.", cxxopts::value<size_t>())
            ("end", "Ending second for mix.", cxxopts::value<size_t>())
            ("dryWet", "Degree of mixing.", cxxopts::value<size_t>())
            ("feedBack", "Number of repetitions.", cxxopts::value<size_t>())
            ("temp", "Period of repetitions(ms).", cxxopts::value<size_t>())
            ("timeOfDelay", "The time of one echo(ms).", cxxopts::value<size_t>());
    options.parse_positional({"begin", "end", "dryWet", "feedBack", "temp", "timeOfDelay"});

    cxxopts::ParseResult result;
    const size_t parametersQuantity = 6;
    if ((r = getParseResult(parametersQuantity, options, result)) != 0) {
        return r;
    }

    this->inputStreamInfo = pair(0, pair(result["begin"].as<size_t>(), result["end"].as<size_t>()));
    this->dryWetDegree = result["dryWet"].as<size_t>();
    this->feedBack = result["feedBack"].as<size_t>();
    this->temp = result["temp"].as<size_t>();
    this->timeOfDelay = result["timeOfDelay"].as<size_t>();

    return r;
}

int NsuConverterI::getParseResult(const size_t parametersQuantity,
                                    cxxopts::Options &options, cxxopts::ParseResult &result) {
    istringstream iss(this->parameters);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(word);
    }

    const char* charArray[20]; // parameter can be max in 20 symbols
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

int NsuConverterI::checkParameters(vector<BinaryStreamIn*> &inputsVector) {
    WAVHeader *inputInfo = inputsVector[this->inputStreamInfo.first]->getHeader();
    try {
        if (this->inputStreamInfo.second.first > this->inputStreamInfo.second.second) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
    try {
        if (this->inputStreamInfo.second.second > (inputInfo->dataSize / inputInfo->sampleRate / inputInfo->bytePerSample)) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders, you out from file border.");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
    return 0;
}

int NsuMute::checkUniqueParameters(vector<BinaryStreamIn*> &) {
    return 0;
}

int NsuMix::checkUniqueParameters(vector<BinaryStreamIn*> &inputsVector) {
    WAVHeader *inputInfo = inputsVector[this->mixStream.first]->getHeader();
    try {
        if (this->mixStream.second >
            (inputInfo->dataSize / inputInfo->sampleRate / inputInfo->bytePerSample)) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders, you out from file border.");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
    try {
        if (((this->inputStreamInfo.second.second - this->inputStreamInfo.second.second)+ this->mixStream.second) >
            (inputInfo->dataSize / inputInfo->sampleRate / inputInfo->bytePerSample)) {
            throw IncorrectParametersFormatException(this->parameters, "Incorrect borders, you out from file border.");
        }
    } catch (IncorrectParametersFormatException &ex) {
        cerr << ex.what() << endl;
        return ex.getErrorCode();
    }
    return 0;
}

int Delay::checkUniqueParameters(vector<BinaryStreamIn *> &) {
    return 0;
}
