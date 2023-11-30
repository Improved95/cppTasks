#include "Converter.h"
#include "FilesParser.h"
#include "Exceptions.h"
#include <fstream>
using std::ifstream;
using std::cerr;
using std::endl;

int NsuSoundProcessorManager::convert() {
    int r;
    NsuSoundProcessorConfigParser filesParser;


    ifstream configFile;
    try {
        configFile.open(arguments[0]);
        if (!configFile.is_open()) {
            throw FileNotOpenException("Config file couldn't open.");
        }
    } catch (FileNotOpenException &ex) {
        cerr << ex.ex_what() << endl;
        return ex.getErrorCode();
    }

    vector<string> parameters;
    bool stopReadingFile = false;
    while (!stopReadingFile) {
        r = filesParser.parse(configFile, parameters, stopReadingFile);
        // создать класс конвертера на основе парсера
    }

    configFile.close();
    return r;
}
