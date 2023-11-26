#include "SoundProcessor.h"

int ParsersExceptions::cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[], cxxopts::Options options) {
    try {
        result = options.parse(argc, argv);
    } catch (exception &ex) {
        std::cerr << ex.what() << endl;
        std::cerr << options.help() << endl;
        return 1;
    }
    return 0;
}

