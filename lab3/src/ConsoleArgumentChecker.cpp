#include "Life.h"

void ParserConsoleParametersAndInitialGame::parseAndInitial(int argc, char **argv, Life *gameObject) {
    ifstream fileIn;
    ofstream fileOut;
    size_t tickQuantity;


    switch(argc) {
        case 4:
            fileOut.open(argv[3]);
            if (!fileOut.is_open()) {
                cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
                gameObject->gameWithoutInitialData();
                break;
            }
            try {
                tickQuantity = std::stoull(argv[2]);
                if (tickQuantity == 0ULL) {
                    throw exception();
                }
            } catch (const exception &ex) {
//                cout << ex.what() << endl;
                cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
                gameObject->gameWithoutInitialData();
                break;
            }
        case 2:
            fileIn.open(argv[1]);
            if (!fileIn.is_open()) {
                cout << "Incorrect output file path. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
                gameObject->gameWithoutInitialData();
                break;
            }
            if (argc == 2) {
                gameObject->gameWithInitialData(fileIn);
            } else if (argc == 4) {
                gameObject->offlineGame(fileIn, tickQuantity, fileOut);
            }
            break;
        default:
            cout << "Incorrect input. You need enter path to input file, quantity ticks, path to output file. Example: 'fileIn.life' 5 'fileOut.life'" << endl;
            break;
    }
    fileIn.close();
    fileOut.close();
}
