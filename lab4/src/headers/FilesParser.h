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

class FilesParser {
public:
    virtual int parse(ifstream &, vector<string> &, bool &stopReadingFile) = 0;
};

class NsuConvertersInfo {
protected:
    static const size_t convertersQuantity = 2;
};

class NsuSoundProcessorFilesParser : public FilesParser, public NsuConvertersInfo {
public:
    static const string* getConvertersName() { return convertersNames; }
    static size_t getConvertersQuantity() { return convertersQuantity; }
protected:
    static const string convertersNames[convertersQuantity];
    static const string ConvertersNamesPatterns;
};

class NsuSoundProcessorConfigParser : public NsuSoundProcessorFilesParser {
public:
    virtual int parse(ifstream &config, vector<string> &parameters, bool &stopReadingFile) override;
};

/*==================================================================================================*/

class ConverterParametersParser {
public:
    virtual int parse(string &parameters) = 0;
};

class NsuSoundProcessorParametersParser : public ConverterParametersParser, public NsuConvertersInfo {
public:
    static const string patternsOfConverterNamesWithParameters[convertersQuantity];
};

class NsuMuteConverterParametersParser : public NsuSoundProcessorParametersParser {
public:
    virtual int parse(string &parameters) override;
};

class NsuMixConverterParametersParser : public NsuSoundProcessorParametersParser {
    virtual int parse(string &parameters) override;
};

class ConverterParametersParserFactory {
    //класс пустышка(хз, можно так или нет)
};

class NsuConverterParametersParserFactory : public ConverterParametersParserFactory{
public:
    static const unordered_map<string, function<ConverterParametersParser*()>> parametersParserRegistry;
};

#endif
