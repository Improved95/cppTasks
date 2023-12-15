#include "SoundProcessor.h"

int main(int argc, char *argv[]) {
    int r;

    SoundProcessor soundProcessor;
    r = soundProcessor.convertWithConsoleArguments(argc, argv);

    return r;
}