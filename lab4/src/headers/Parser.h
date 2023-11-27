#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
using std::vector;
using std::string;

class ParseConsoleArguments {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, string &config, string &output, vector<string> &inputs);
};

#endif
