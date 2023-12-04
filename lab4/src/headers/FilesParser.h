#ifndef FILES_PARSER
#define FILES_PARSER

#include <iostream>
#include <fstream>
#include <vector>
#include "Converter.h"
using std::ifstream;
using std::string;
using std::vector;

class NsuSoundProcessorConfigParser {
public:
    int parse(ifstream &config, vector<NsuConverterI*> &convertersVector);

private:
    string checkConverterName(string &parameterStr);
    static const string parametersPattrerm;
};

#endif
