#include "../headers/CountWordsClass.h"
#include "gtest/gtest.h"
using namespace std;

TEST(task1, countWords) {
    //arrange
    CountWordsClass classObj1;
    
    //act
    stringstream inputTestStroke, outTestStroke;
    inputTestStroke << "one two" << endl;
    classObj1.countingWordsFromFile(inputTestStroke, outTestStroke);

    //assets
    EXPECT_EQ(outTestStroke.str(), "one;1;50\ntwo;1;50\n");

    //arrange
    istream fileIn("in.txt");
    ostream fileOut("out.txt");

    //act
    outTestStroke.str("");
    classObj1.countingWordsFromFile(inputTestStroke, outTestStroke);

    //assets
    EXPECT_EQ(outTestStroke.str(), "one;2;50\ntwo;2;50\n");
}
