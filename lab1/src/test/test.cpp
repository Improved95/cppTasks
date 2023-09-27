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
    vector<pair<string, int>> mapVector = classObj1.mapSort();

    //assets
    vector<pair<string, int>> checkVector {{"one", 1}, {"two", 1}};
    EXPECT_EQ(mapVector == checkVector, true);
    EXPECT_EQ(outTestStroke.str(), "one;1;50\ntwo;1;50\n");

    //act
    stringstream inputTestStroke2, outTestStroke2;
    inputTestStroke2 << "one two one two";
    classObj1.countingWordsFromFile(inputTestStroke2, outTestStroke2);
    mapVector = classObj1.mapSort();

    // assets
    checkVector = {{"one", 3}, {"two", 3}};
    EXPECT_EQ(mapVector == checkVector, true);
    EXPECT_EQ(outTestStroke2.str(), "one;3;50\ntwo;3;50\n");
}
