#include "Messages.h"

void ShowMessages::showMessage(string &message) const {
    cout << message << endl;
}

void ShowError::cerrError(string &message) const {
    cerr << message << endl;
}

void ShowInfo::coutConfigExample() {
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
