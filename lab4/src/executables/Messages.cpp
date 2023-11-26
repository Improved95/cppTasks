#include "Messages.h"

void ShowMessages::showMessage(string &message) const {
    cout << message << endl;
}

void ShowError::cerrError(string &message) const {
    cerr << message << endl;
}

void ShowInfo::coutInstruction() {
    cout << "Describe in config.txt used converters and their parameters. Converters are applied sequentially." << endl;
    cout << "You have 3 options of convert:\n"
            "mute <t1> <t2>\t\t - Mute input1 from t1 to t2 seconds input1;\n"
            "mix <t1> <t2> $2 <t3>\t - Mix input1 from t1 to t2 second with input2 starts from t3 second;\n"
            "third convert...\n" << endl;
    cout << "config.txt example:" << endl;
    cout << "# Mute first 30s in input1\n"
            "mute 0 30\n"
            "\n"
            "# Mix input1 with input2, start from 10s\n"
            "mix $2 10\n"
            "\n"
            "# Mute third minute in mixed stream\n"
            "mute 120 180\n" << endl;
}
