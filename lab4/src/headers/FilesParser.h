#ifndef FILES_PARSER
#define FILES_PARSER

#include <iostream>
#include <fstream>
#include <vector>
#include "Converter.h"
#include "Streams.h"
using std::ifstream;
using std::string;
using std::vector;

class NsuSoundProcessorConfigParser {
public:
    int parse(StreamIn &config, vector<NsuConverterI*> &convertersVector, size_t &createNumber);

private:
    string checkConverterName(string &parameterStr);
    static const string parametersPattrerm;
};

#endif
