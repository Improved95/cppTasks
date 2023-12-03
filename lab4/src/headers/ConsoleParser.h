#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "cxxopts.hpp"
#include "Messages.h"
using std::vector;
using std::string;

class ParseConsoleArguments {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, vector<string> &arguments);

    string checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option);
    void argumentIsExist(const string &optionName, cxxopts::ParseResult &result, cxxopts::Options &options);

private:
    static const size_t quantityModes = 2;
    static const string mutuallyArguments[quantityModes];
};

class ParseArgumentsForNsuSoundProcessor : public ParseConsoleArguments {
public:
    int parseFilesArguments(char *argv[], cxxopts::ParseResult &result,
                            cxxopts::Options &options, vector<string> &arguments);
};

class ParseFileName {
protected:
    static const string namePattern;
    static const string anyExtensionPattern;
    virtual void checkFileName(const string &fileName, const cxxopts::Options &options) = 0;
};

class ParseFileNameWithAnyExtension : public ParseFileName {
public:
    void checkFileName(const string &fileName, const cxxopts::Options &options) override;
};

class ParseFileNameWithSoundsExtension : public ParseFileName {
public:
    void checkFileName(const string &fileName, const cxxopts::Options &options) override;

private:
    static const size_t quantitySoundExtensions = 1;
    static const string soundExtensions[quantitySoundExtensions];
};

#endif
