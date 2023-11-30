#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "cxxopts.hpp"
#include "Messages.h"
#include <unordered_map>
#include <functional>
using std::vector;
using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::make_unique;
using std::function;

class ParseArgumentsForNSUSoundProcessor;
class CoutHelp;

class ParseConsoleArguments : public ConvertStringToChar {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, string &config,
                                        string &output, vector<string> &inputs);

    string checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option);
    void argumentIsExist(const char *optionName, cxxopts::ParseResult &result, cxxopts::Options &options);

    static unique_ptr<ParseConsoleArguments> parsersCreator;
private:
    static const size_t quantityModes = 2;
    static const char* const mutuallyArguments[quantityModes];
    static const unordered_map<string, function<ParseConsoleArguments()>> parsersRegistry;

    ParseConsoleArguments creatorUniqueParsers(string &mode);
};

class CoutHelp : public ParseConsoleArguments {

};

class ParseArgumentsForNSUSoundProcessor : public ParseConsoleArguments {
public:
    int parseFilesArguments(char *argv[], cxxopts::ParseResult &result, cxxopts::Options &options,
                            string &config, string &output, vector<string> &inputs);
};

class ParseFileName : public ConvertStringToChar {
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
