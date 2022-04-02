#include <gtest/gtest.h>
#include <string>
extern "C" {
#include "parallel_processing.h"
}

#define SUCCESS_FLAG false


TEST(StartProcessTest, InCorrectInput1) {
    int result = start_process(NULL, NULL, NULL, 0, 5);

    EXPECT_EQ(result, 1);
}

TEST(FindSequencesTest, InCorrectInput1) {
    bool result = find_sequences(0);

    EXPECT_EQ(result, 1);
}
