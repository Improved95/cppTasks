#include <regex>
#include "FilesParser.h"
#include "Exceptions.h"
#include "Converter.h"
#include "Streams.h"
using std::ifstream;
using std::regex;
using std::smatch;
using std::regex_search;
using std::regex_match;
using std::istringstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::convert() {
    int r;
    NsuSoundProcessorConfigParser filesParser;


    ifstream configFile;
    try {
        configFile.open(arguments[0]);
        if (!configFile.is_open()) {
            throw FileNotOpenException(arguments[0]);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    vector<NsuConverterI*> convertersVector;
    if ((r = filesParser.parse(configFile, convertersVector)) != 0) {
        return r;
    }

    ofstream fileOut;
    fileOut.open(arguments[1]);
    try {
        if (!fileOut.is_open()) {
            throw FileNotOpenException(arguments[1]);
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        cerr << ex.getErrorCode() << endl;
    }

    StreamOut streamOut(&fileOut);

    for (auto &el : convertersVector) {
        el->parseParameters();
    }
    while(NsuConverterI::convertersIsOver(convertersVector)) {
        for (auto &el : convertersVector) {
            el->convert();
        }
    }

    configFile.close();
    return r;
}

bool NsuConverterI::convertersIsOver(const vector<NsuConverterI *> &convertersVector) {
    for (auto &el : convertersVector) {
        if (el->convertingIsComplete) {
            return true;
        }
    }
    return false;
}

size_t NsuConverterI::orderCreation = 0;
const string NsuMute::parametersPattern = "([\\d]+[ ][\\d]+){1}";
int NsuMute::parseParameters() {
    int r;

    try {
        regex pattern(parametersPattern);
        if (regex_match(this->parameters, pattern)) {
             throw IncorrectConvertersParametersException(this->parameters, "mute");
        }
    } catch (IncorrectConvertersParametersException &ex) {
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
            throw IncorrectConvertersParametersException(this->parameters, "mix");
        }
    } catch (IncorrectConvertersParametersException &ex) {
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
    if ((r = fillUsingThreads(2, options, result)) != 0) {
        return r;
    }
    this->usingStream = pair(0, pair(result["begin"].as<int>(), result["end"].as<int>()));

    string referenceOnMixInputStr = result["begin"].as<string>();
    size_t referenceOnMixInput = std::stoull(referenceOnMixInputStr.substr(1, referenceOnMixInputStr.size()));
    this->mixStream = pair(referenceOnMixInput, result["beginMixInput"].as<int>());

    return r;
}

int NsuConverterI::fillUsingThreads(size_t parametersQuantity, cxxopts::Options &options, cxxopts::ParseResult &result) {
    istringstream iss(this->parameters);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
    const char* charArray[parametersQuantity + 1];
    for (size_t i = 0; i < words.size(); i++) {
        charArray[i + 1] = words[i].c_str();
    }

    try {
        result = options.parse(3, charArray);
    } catch (cxxopts::exceptions::exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    return 0;
}

void NsuMute::convert() {

}

void NsuMix::convert() {

}
