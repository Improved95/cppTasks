#ifndef MESSAGES
#define MESSAGES

#include <iostream>
#include <string>
using std::string;

class ShowMessages {
public:
    void showMessage(string &message) const;
};

class ShowInfo : public ShowMessages {
public:
    void coutInstruction();
};

class Concatenation {
public:
    const char *concatenateTwoConstChar(const char *m1, const char *m2);
    const char *concatenateStrAndChar(const char *m1, const string &m2);
    const char *concatenateStrAndChar(const string &m1, const char *m2);
private:
    const char *concatenatingStrAndChar(const char *m1, const string &m2);
};

#endif
