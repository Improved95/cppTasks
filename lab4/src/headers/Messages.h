#ifndef MESSAGES
#define MESSAGES

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cerr;
using std::endl;

class ShowMessages {
public:
    void showMessage(string &message) const;
};

class ShowInfo : public ShowMessages {
public:
    void coutInstruction();
};

class ConvertStringToChar {
public:
    const char *convertToChar(const char *whatsHappend, const char *withWhat);
};

#endif
