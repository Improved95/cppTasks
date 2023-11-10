#include "Life.h"
#include <fstream>
using std::cout;
using std::endl;
using std::exception;

void ParserConsoleParameters::parseAndInitial(int argc, char **argv, Life *gameObject) {
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open(argv[1]);
    fileOut.open(argv[3]);
    size_t tickQuantity;

    if (argc == 2) {
        if (!fileIn.is_open()) {
            cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            gameObject->initialField();
            goto END_FUNCTION_AND_CLOSE_FILES;
        }
    }
    if (argc == 4) {
        if (!fileOut.is_open()) {
            cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            gameObject->initialField();
            goto END_FUNCTION_AND_CLOSE_FILES;
        }
        ExceptionHandling exceptionHandling;
        if (!exceptionHandling.sttoullIsCorrect(tickQuantity, argv[2], "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'")) {
            gameObject->initialField();
            goto END_FUNCTION_AND_CLOSE_FILES;
        }
    }
    if (argc != 2 && argc != 4) {
        cout << "Incorrect input. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
        gameObject->initialField();
        goto END_FUNCTION_AND_CLOSE_FILES;
    }

    if (argc == 2) {
        gameObject->initialField(fileIn);
    } else if (argc == 4) {
        gameObject->initialField(fileIn, tickQuantity, fileOut);
    }

    END_FUNCTION_AND_CLOSE_FILES:
    fileIn.close();
    fileOut.close();
}
