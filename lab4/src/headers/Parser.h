#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "cxxopts.hpp"
#include "Messages.h"
using std::vector;
using std::string;
using std::regex;
using std::regex_match;

class ParseConsoleArguments : public ConvertStringToChar {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, string &config,
                                        string &output, vector<string> &inputs);

private:
    const char* mutuallyArguments[2] = {"help", "convert"};
    void checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option);
    void argumentIsExist(const char *optionName, cxxopts::ParseResult &result, cxxopts::Options &options);
};

class ParseFileName : public ConvertStringToChar {
protected:
    const string namePattern = "[A-Za-z0-9]+[.]";
    const string anyExtensionPattern = "[a-z]*";
    virtual void checkFileName(const char *fileName, const cxxopts::ParseResult &result,
                               const cxxopts::Options &options, const char *optionName) = 0;
};

class ParseFileNameWithAnyExtension : public ParseFileName {
public:
    void checkFileName(const char *fileName, const cxxopts::ParseResult &result,
                       const cxxopts::Options &options, const char *optionName) override;
};

class ParseFileNameWithSoundsExtension : public ParseFileName {
public:
    void checkFileName(const char *fileName, const cxxopts::ParseResult &result,
                       const cxxopts::Options &options, const char *optionName) override;

private:
    const char* soundExtensions[1] = {"wav"};
};

#endif
