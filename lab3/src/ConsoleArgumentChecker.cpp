#include "Life.h"

void ParserConsoleParametersAndInitialGame::parseAndInitial(int argc, char **argv, Life *gameObject) {
    ifstream fileIn;
    ofstream fileOut;
    size_t tickQuantity;
    if (argc == 2) {
        fileIn.open(argv[1]);
        if (!fileIn.is_open()) {
            cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            gameObject->initialField();
            goto END_FUNCTIONS_AND_CLOSE_FILES;
        }
    }
    if (argc == 4) {
        fileOut.open(argv[3]);
        if (!fileOut.is_open()) {
            cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            gameObject->initialField();
            goto END_FUNCTIONS_AND_CLOSE_FILES;
        }
        try {
            tickQuantity = std::stoull(argv[2]);
            if (tickQuantity == 0ULL) {
                throw exception();
            }
        } catch (const exception &ex) {
//            cout << ex.what() << endl;
            cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            gameObject->initialField();
            goto END_FUNCTIONS_AND_CLOSE_FILES;
        }
    }
    if (argc != 2 && argc != 4) {
        cout << "Incorrect input. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
        gameObject->initialField();
        goto END_FUNCTIONS_AND_CLOSE_FILES;
    }

    if (argc == 2) {
        gameObject->initialField(fileIn);
    } else if (argc == 4) {
        gameObject->initialField(fileIn, tickQuantity, fileOut);
    }

    END_FUNCTIONS_AND_CLOSE_FILES:
    fileIn.close();
    fileOut.close();
}
