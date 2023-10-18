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
    for (size_t i = 0; i < 2; i++) {
        cb1.push_back(i + 1);
    }

    cb1.insert(2, 10);
    EXPECT_EQ(cb1.getSize(), 3);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 0);
    EXPECT_EQ(cb1.getEndPosInBuf(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 10, 0));

    cb1.insert(2, 20);
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 1);
    EXPECT_EQ(cb1.getEndPosInBuf(), 0);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 20, 10));

    cb1.push_back(11);
    cb1.push_back(12);
    cb1.pop_back();

    cb1.insert(2, 30);
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(30, 11, 20, 10));

    cb1.pop_back();

    cb1.insert(0, 40);
    EXPECT_EQ(cb1.getSize(), 4);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(10, 30, 40, 20));


    cb1.insert(2, 50);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(10, 50, 40, 20));
}

TEST(CircularBuffer, erase) {
    CircularBuffer<int> cb2(5);
    for (size_t i = 0; i < 5; i++) {
        cb2.push_back(i + 1);
    }

    cb2.erase(3, 4);

    EXPECT_EQ(cb2.getSize(), 4);
    EXPECT_EQ(cb2.getBeginPosInBuf(), 0);
    EXPECT_EQ(cb2.getEndPosInBuf(), 4);
    EXPECT_THAT(cb2.getBeginBufferInMem(), testing::ElementsAre(1, 2, 3, 5, 4));

    cb2.insert(1, 10);
    cb2.erase(3, 5);

    EXPECT_EQ(cb2.getSize(), 3);
    EXPECT_EQ(cb2.getBeginPosInBuf(), 0);
    EXPECT_EQ(cb2.getEndPosInBuf(), 3);
    EXPECT_THAT(cb2.getBeginBufferInMem(), testing::ElementsAre(1, 10, 2, 3, 5));

    CircularBuffer<int> cb1(5);
    for (size_t i = 0; i < 7; i++) {
        cb1.push_back(i + 1);
    }

    cb1.erase(1, 3);
    EXPECT_EQ(cb1.getSize(), 3);
    EXPECT_EQ(cb1.getBeginPosInBuf(), 2);
    EXPECT_EQ(cb1.getEndPosInBuf(), 0);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(4, 5, 3, 6, 7));

}

TEST(CircularBuffer, rotate) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    cb1.rotate(1);

    EXPECT_EQ(cb1.getBeginPosInBuf(), 0);
    EXPECT_EQ(cb1.getEndPosInBuf(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(4, 5, 6, 3));

    cb1.rotate(3);

    EXPECT_EQ(cb1.getBeginPosInBuf(), 2);
    EXPECT_EQ(cb1.getEndPosInBuf(), 1);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(6, 3, 4, 5));

    CircularBuffer<int> cb2(4);
    for (size_t i = 0; i < 3; i++) {
        cb1.push_back(i + 1);
    }

    cb1.rotate(2);

    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(2, 3, 6, 1));
}

TEST(CircularBuffer, linearize) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    cb1.rotate(0);

    EXPECT_EQ(cb1.getBeginPosInBuf(), 3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 2);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(3, 4, 5, 6));
}

TEST(CircularBuffer, set_capacity) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    cb1.set_capacity(5);
    EXPECT_EQ(cb1.getCapacity(), 5);
}

TEST(CircularBuffer, oper) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    CircularBuffer<int> cb2(4);
    for (size_t i = 0; i < 6; i++) {
        cb2.push_back(i + 1);
    }

    EXPECT_EQ(cb1 == cb2, 1);
    EXPECT_EQ(cb1 != cb2, 0);

    CircularBuffer<int> cb3(4);
    for (size_t i = 0; i < 6; i++) {
        cb3.push_back(i * 10);
    }

    cb1 = cb3;
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(40, 50, 20, 30));
}

TEST(CircularBuffer, resize) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 3; i++) {
        cb1.push_back(i + 1);
    }

    cb1.resize(4, 10);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 3, 10));

    cb1.resize(3);
    EXPECT_EQ(cb1.getEndPosInBuf(), 3);
    EXPECT_THAT(cb1.getBeginBufferInMem(), testing::ElementsAre(1, 2, 3, 10));
}

TEST(CircularBuffer, frontBack) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 3; i++) {
        cb1.push_back(i + 1);
    }

    EXPECT_EQ(cb1.front(), 1);
    EXPECT_EQ(cb1.back(), 3);
}

TEST(CircularBuffer, isLinearized) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    EXPECT_EQ(cb1.is_linearized(), 0);

    cb1.linearize();
    EXPECT_EQ(cb1.is_linearized(), 1);
}

TEST(CircularBuffer, emptyFull) {
    CircularBuffer<int> cb1(4);
    for (size_t i = 0; i < 6; i++) {
        cb1.push_back(i + 1);
    }

    EXPECT_EQ(cb1.empty(), 0);

    cb1.clear();
    EXPECT_EQ(cb1.empty(), 1);

    /*======================*/

    for (size_t i = 0; i < 3; i++) {
        cb1.push_back(i + 1);
    }
    EXPECT_EQ(cb1.full(), 0);

    for (size_t i = 0; i < 4; i++) {
        cb1.push_back(i + 1);
    }
    EXPECT_EQ(cb1.full(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
