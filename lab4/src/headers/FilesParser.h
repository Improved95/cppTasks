#ifndef FILES_PARSER
#define FILES_PARSER

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Messages.h"
using std::ifstream;
using std::string;
using std::vector;
using std::function;
using std::unordered_map;

class FilesParser : public Concatenation {
public:
    virtual int parse(ifstream &, vector<string> &) = 0;

    static const char** getConvertersName() {
        return convertersNames;
    }
protected:
    static const size_t quantityConverter = 2;
    static const char* convertersNames[quantityConverter];
    static const char* converterNamesWithParametersPatterns[quantityConverter];
    static const char* convertersNamesPattern;
};

class NsuSoundProcessorConfigParser : public FilesParser {
public:
    virtual int parse(ifstream &config, vector<string> &parameters) override;
};

class ConverterParametersParser {
public:
    virtual void parse(string &parameters) = 0;
};

class MuteConverterParametersParser : public ConverterParametersParser {
    virtual void parse(string &parameters) override;
};

class MixConverterParametersParser : public ConverterParametersParser {
    virtual void parse(string &parameters) override;
};

class ConverterParametersParserFactory {
public:
    static const unordered_map<string, function<ConverterParametersParser*()>> parametersParserRegistry;
private:
};

#endif
