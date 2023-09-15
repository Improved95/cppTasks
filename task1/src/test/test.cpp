#include "../headers/countWordsClass.h"
#include "gtest/gtest.h"
using namespace std;

TEST(task1, countWords) {
    //arrange
    fstream fileIn, fileOut, checkFile;
    fileIn.open("in.txt", fstream::out);
    fileOut.open("out.txt", fstream::out);
    ASSERT_EQ((fileIn.is_open() && fileOut.is_open()), true);
    countWordsClass classObj;

    //act
    fileIn << "one two three pragme one two one one" << endl;
    fileIn.close();

    fileIn.open("in.txt", fstream::in);
    classObj.callMainFunctions(fileIn, fileOut);
    fileIn.close();
    fileOut.close();
    
    checkFile.open("out.txt", fstream::in);
    string line;
    stringstream fileContent;
    while(getline(checkFile, line)) {
        fileContent << line << "\n";
    }
    checkFile.close();

    //assert
    EXPECT_EQ(fileContent.str(), "one;4;50\ntwo;2;25\npragme;1;12.5\nthree;1;12.5\n");

    //act
    fileIn.open("in.txt", fstream::out);
    fileOut.open("out.txt", fstream::out);

    fileIn << "strat caster lesPaul explorer strat explorer strat" << endl;
    fileIn.close();

    fileIn.open("in.txt", fstream::in);
    classObj.callMainFunctions(fileIn, fileOut);
    fileIn.close();
    fileOut.close();

    checkFile.open("out.txt", fstream::in);
    fileContent.str("");
    while(getline(checkFile, line)) {
        fileContent << line << "\n";
    }
    checkFile.close();
    EXPECT_EQ(fileContent.str(), "strat;3;42.8571\nexplorer;2;28.5714\ncaster;1;14.2857\nlesPaul;1;14.2857\n");
}
