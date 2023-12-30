#ifndef MESSAGES
#define MESSAGES

#include <iostream>
#include <string>
using std::string;

class ShowMessages {
public:
    void showMessage(const string &message) const;
};

class ShowInfo : public ShowMessages {
public:
    void coutInstruction();
};

#endif
