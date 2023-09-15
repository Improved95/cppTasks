#include "../headers/countWordsClass.h"
#include "gtest/gtest.h"
using namespace std;

TEST(task1, countWords) {
    //arrange
    fstream fileIn, fileOut;
    fileIn.open("in.txt", fstream::in);
    fileOut.open("out.txt", fstream::out);
    countWordsClass classObj;

    //act
    classObj.callMainFunctions(fileIn, fileOut);
    fileIn.close();
    fileOut.close();
    
    ifstream checkFile("out.txt");
    string line;
    stringstream fileContent;
    while(getline(checkFile, line)) {
        fileContent << line << "\n";
    }
    checkFile.close();

    //assert
    EXPECT_EQ(fileContent.str(), "one;4;50\ntwo;2;25\npragme;1;12.5\nthree;1;12.5\n");
}
