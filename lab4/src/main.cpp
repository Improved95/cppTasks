#include "SoundProcessor.h"

int main(int argc, char *argv[]) {
    int r;

    SoundProcessor soundProcessor;
    r = soundProcessor.convertWithConsoleParameters(argc, argv);

    return r;
}