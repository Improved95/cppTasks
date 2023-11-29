#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "cxxopts.hpp"
#include "Messages.h"
#include <unordered_map>
using std::vector;
using std::string;
using std::unordered_map;
using std::unique_ptr;

class MethodsFabric;

class ParseConsoleArguments : public ConvertStringToChar {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv, string &config,
                                        string &output, vector<string> &inputs);

    string & checkMutuallyArguments(cxxopts::ParseResult &result, cxxopts::Options &option);
    void argumentIsExist(const char *optionName, cxxopts::ParseResult &result, cxxopts::Options &options);

private:
    const char* mutuallyArguments[2] = {"help", "convert"};
//    const unordered_map<string, > methods = {
//
//    };
};

class ModesWorkingFactory {
public:
    using ConverterCreator = unique_ptr<ParseConsoleArguments> (*)();
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
