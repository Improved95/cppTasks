#include "Messages.h"
using std::cout;
using std::endl;

void ShowMessages::showMessage(const string &message) const {
    cout << message << endl;
}

void ShowInfo::coutInstruction() {
    const string message =  "Describe in config.txt used converters and their parameters. Converters are applied sequentially.\n"
                      "You have 3 options of convert:\n"
                      "mute <t1> <t2> - Mute input1 from t1 to t2 seconds input1;\n"
                      "mix <t1> <t2> -i <2> <t3> - Mix input1 from t1 to t2 second with input2 starts from t3 second;\n"
                      "delay <t1> <t2> <Dry/Wet(int (0-100))> <FeedBack(int)> <Temp(int)> <Time Of delay(int)>  - Creates an echo effect of the original sound from t1 to t2.\n"
                      "Parameters: Degree of mixing; Number of repetitions; Period of repetitions(ms); The time of one echo(ms).\n"
                      "\n\nconfig.txt example:\n"
                      "# Mute first 30s in input1\n"
                      "mute 0 30\n"
                      "\n# Mix input1 with input2, start from 10s"
                      "\nmix $2 10\n"
                      "\n# Mute third minute in mixed stream"
                      "\nmute 120 180";
    showMessage(message);
}
