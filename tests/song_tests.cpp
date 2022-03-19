#include <gtest/gtest.h>

extern "C" {
#include "song_tools.h"
}

TEST(PrintSongTest, CorrectDataPrint) {
    Song test_song = {"Title", "Author", "Performer", {3, 55}};
    int printing_result = print_song(&test_song);
    EXPECT_EQ(printing_result, 65);
}

TEST(GetSongTest, NullPointerTest) {
    bool getting_result = get_song(nullptr);

    EXPECT_EQ(getting_result, true);
}


TEST(GetDurationTest, NullPointerTest) {
    bool getting_result = get_duration(nullptr);

    EXPECT_EQ(getting_result, true);
}
