#include "CircularBuffer.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using circularBuffer::CircularBuffer;

TEST(lab2, circularBuffer) {
    CircularBuffer<int> cb1(3);

    for(size_t i = 0; i < cb1.getSize(); i++) {
        cb1[i] = i;
    }

    EXPECT_EQ(cb1.getSize(), 3)
    EXPECT_THAT(cb1.getBeginBufferInMem(), ElementsAre(0, 1, 2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
