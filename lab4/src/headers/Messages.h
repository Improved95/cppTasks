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

class ShowError : public ShowMessages {
public:
    void cerrError(string &message) const;
};

class ShowInfo : public ShowMessages {
public:
    void coutConfigExample() ;
};

#endif
