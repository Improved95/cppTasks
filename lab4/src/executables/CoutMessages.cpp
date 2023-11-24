#include "../headers/SoundProcessor.h"

void CoutMessages::coutErrorAndHelp(string message) {
    cout << message << endl;
    coutHelp();
}

void CoutMessages::coutHelp() {
    cout << "You should initial converter with next arguments:\n"
            "Help - ./SoundProcessor -h\n"
            "Converter - ./SoundProcessor -c config.txt output.wav input1.wav [<input2.wav ...]" << endl;
}

void CoutMessages::coutError(string message) {
    cout << message << endl;
}
