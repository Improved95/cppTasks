#ifndef FILES_PARSER
#define FILES_PARSER

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Messages.h"
using std::ifstream;
using std::string;
using std::vector;
using std::unordered_map;

class FilesParser {
public:
    virtual int parse(ifstream &, vector<string> &) = 0;
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
    virtual int parse(ifstream &config, vector<string> &parameters) override;

private:
    string checkConverterName(string &parameterStr);
};

/*==================================================================================================*/

class NSUconvertersFactory {
public:
private:

};

#endif
