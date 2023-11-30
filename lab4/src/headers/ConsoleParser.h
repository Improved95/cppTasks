#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "cxxopts.hpp"
#include "Messages.h"
using std::vector;
using std::string;

class ParseConsoleArguments : public Concatenation {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, vector<string> &arguments);

    string checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option);
    void argumentIsExist(const char *optionName, cxxopts::ParseResult &result, cxxopts::Options &options);

private:
    static const size_t quantityModes = 2;
    static const char* const mutuallyArguments[quantityModes];
};

class ParseArgumentsForNSUSoundProcessor : public ParseConsoleArguments {
public:
    int parseFilesArguments(char *argv[], cxxopts::ParseResult &result,
                            cxxopts::Options &options, vector<string> &arguments);
};

class ParseFileName : public Concatenation {
protected:
    static const string namePattern;
    static const string anyExtensionPattern;
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
    static const size_t quantitySoundExtensions = 1;
    static const char* const soundExtensions[quantitySoundExtensions];
};

#endif
