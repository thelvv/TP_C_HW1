#include <gtest/gtest.h>

extern "C" {
#include "serial_processing.h"
}

#define SUCCESS_FLAG false

TEST(FindSequencesTest, InCorrectInput) {
    int result = find_sequences(0);

    EXPECT_EQ(result, 0);
}

TEST(FindSequencesTest, CorrectInput) {
    int result = find_sequences(42);

    EXPECT_EQ(result, 0);
}
