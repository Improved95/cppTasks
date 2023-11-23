#include "SoundProcessor.h"

void CoutMessages::coutErrorAndHelp(string message) {
    cout << message << endl;
    coutHelp();
}

void CoutMessages::coutHelp() {
    cout << "You should initial converter with next parameters:\n"
            "Help - ./SoundProcessor -h\n"
            "Converter- ./SoundProcessor -c config.txt output.wav input1.wav [<nput2.wav …]" << endl;
}
