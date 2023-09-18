#include "../headers/CountWordsClass.h"
#include "gtest/gtest.h"
using namespace std;

TEST(task1, countWords) {
    //arrange
    CountWordsClass classObj1;
    
    //act
    stringstream inputTestStroke, outTestStroke;
    inputTestStroke << "one two";
    classObj1.countingWordsFromFile(inputTestStroke, outTestStroke);

    //assets
    vector<pair<string, int>> mapVector = classObj1.mapSort();
    vector<pair<string, int>> checkVector {{"one", 1}, {"two", 1}};

    EXPECT_EQ(mapVector == checkVector, true);
    EXPECT_EQ(outTestStroke.str(), "one;1;50\ntwo;1;50\n");

    //act
    classObj1.countingWordsFromFile(inputTestStroke, outTestStroke);
    checkVector = {{"one", 2}, {"two", 2}};

    // assets
    // EXPECT_EQ(mapVector == checkVector, true);
    // EXPECT_EQ(outTestStroke.str(), "one;1;50\ntwo;1;50\n");
}
