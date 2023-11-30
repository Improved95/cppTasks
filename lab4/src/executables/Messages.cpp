#include "Messages.h"
using std::cout;
using std::endl;

void ShowMessages::showMessage(string &message) const {
    cout << message << endl;
}

void ShowInfo::coutInstruction() {
    string message =  "Describe in config.txt used converters and their parameters. Converters are applied sequentially.\n"
                      "You have 3 options of convert:\n"
                      "mute <t1> <t2>\t\t - Mute input1 from t1 to t2 seconds input1;\n"
                      "mix <t1> <t2> $2 <t3>\t - Mix input1 from t1 to t2 second with input2 starts from t3 second;\n"
                      "third convert...\n"
                      "\nconfig.txt example:\n"
                      "# Mute first 30s in input1\n"
                      "mute 0 30\n"
                      "\n# Mix input1 with input2, start from 10s"
                      "\nmix $2 10\n"
                      "\n# Mute third minute in mixed stream"
                      "\nmute 120 180";
    showMessage(message);
}

const char * Concatenation::concatenateTwoConstChar(const char *m1, const char *m2) {
    string message;
    message.append(m1);
    message += " \"";
    message.append(m2);
    message += "\".";
    return message.c_str();
}

const char *Concatenation::concatenatingStrAndChar(const char *m1, const string &m2) {
    string message;
    message.append(m1);
    message += (string)(" ") + m2;
    return message.c_str();
}

const char *Concatenation::concatenateStrAndChar(const char *m1, const string &m2) {
    return concatenatingStrAndChar(m1, m2);
}

const char *Concatenation::concatenateStrAndChar(const string &m1, const char *m2) {
    return concatenatingStrAndChar(m2, m1);
}


