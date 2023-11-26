#include "SoundProcessor.h"

void CoutMessages::coutErrorAndHelp(string message) {
    cout << message << endl;
//    coutHelp();
}

void CoutMessages::coutConfigExample() {
    cout << "config.txt example:" << endl;
    cout <<
        "# Mute first 30s in input1\n"
        "mute 0 30\n"
        "\n"
        "# Mix input1 with input2, start from 10s\n"
        "mix $2 10\n"
        "\n"
        "# Mute third minute in mixed stream\n"
        "mute 120 180\n"
        << endl;
}

void CoutMessages::coutError(string message) {
    cout << message << endl;
}
