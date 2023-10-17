#include "CircularBuffer.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::string;
using circularBuffer::CircularBuffer;

TEST(CircularBuffer, initial) {
    CircularBuffer<int> cb1(3);

    for(size_t i = 0; i < cb1.getCapacity(); i++) {
        cb1.push_back(i);
    }

    EXPECT_EQ(cb1.getSize(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(0, 1, 2));

    CircularBuffer<string> cb2(3, "test");

    EXPECT_EQ(cb2.getSize(), 3);
    EXPECT_THAT(cb2.getBeginBufferInMem(), testing::ElementsAre("test", "test", "test"));
}

TEST(CircularBuffer, copy) {
    CircularBuffer<string> cb1(2, "test");

    CircularBuffer<string> cb2(cb1);
    EXPECT_EQ(cb2.getSize(), 2);
    EXPECT_THAT(cb2.getBeginBufferInMem(), testing::ElementsAre("test", "test"));
}

TEST(CircularBuffer, swap) {
    CircularBuffer<int> cb1(2, 1);
    CircularBuffer<int> cb2(3, 2);

    cb1.swap(cb2);

    EXPECT_EQ(cb1.getSize(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(2, 2, 2));

    EXPECT_EQ(cb2.getSize(), 2);
    EXPECT_THAT(cb2.getBeginBufferInMem(), testing::ElementsAre(1, 1));
}

TEST(CircularBuffer, push_back) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i);
    }

    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(4, 5, 2, 3));
}

TEST(CircularBuffer, push_front) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 2; i++) {
        cb1.push_back(i + 1);
    }

    cb1.push_front(10);
    cb1.push_front(10);

    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 2);
    EXPECT_EQ(cb1.getEndPosInBuf(), 1);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 10, 10));
}

TEST(CircularBuffer, pop_back) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    cb1.pop_back();
    cb1.pop_back();
    cb1.pop_back();

    EXPECT_EQ(cb1.getSize(), 1);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 2);
    EXPECT_EQ(cb1.getEndPosInBuf(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(5, 6, 3, 4));
}

TEST(CircularBuffer, pop_front) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    cb1.pop_front();
    cb1.pop_front();
    cb1.pop_front();

    EXPECT_EQ(cb1.getSize(), 1);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 1);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(5, 6, 3, 4));
}

TEST(CircularBuffer, insert) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 3; i++) {
        cb1.push_back(i + 1);
    }

    cb1.insert(3, 10);
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 1);
    EXPECT_EQ(cb1.getEndPosInBuf(), 0);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 3, 10));

    cb1.push_back(11);
    cb1.push_back(12);
    cb1.pop_back();

    cb1.insert(0, 20);
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(10, 11, 20, 3));

    cb1.insert(2, 30);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(30, 11, 20, 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
