#include <gtest/gtest.h>

extern "C" {
#include "array_tools.h"
#include "song_tools.h"
}

#define SUCCESS_FLAG false

TEST(AllocateMemoryTest, AllocationTest) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.size, 0);
    EXPECT_EQ(test_array.capacity, 1);

    EXPECT_FALSE(test_array.song_array == nullptr);

    EXPECT_STREQ(test_array.song_array->title, "");
    EXPECT_STREQ(test_array.song_array->author, "");
    EXPECT_STREQ(test_array.song_array->performer, "");
    EXPECT_EQ(test_array.song_array->duration.min, 0);
    EXPECT_EQ(test_array.song_array->duration.sec, 0);

    free(test_array.song_array);
}


TEST(PushSongTest, SingleData) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Song test_song = {"Title", "Author", "Performer", {3, 55}};
    bool push_result = push_song(&test_array, test_song);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_STREQ(test_array.song_array[0].title, test_song.title);
    EXPECT_STREQ(test_array.song_array[0].author, test_song.author);
    EXPECT_STREQ(test_array.song_array[0].performer, test_song.performer);
    EXPECT_EQ(test_array.song_array[0].duration.min, test_song.duration.min);
    EXPECT_EQ(test_array.song_array[0].duration.sec, test_song.duration.sec);

    free(test_array.song_array);
}


TEST(PushSongTest, DoubleData) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Song test_song_1 = {"Title_1", "Author_1", "Performer_1", {1, 11}};
    bool push_result = push_song(&test_array, test_song_1);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_STREQ(test_array.song_array[0].title, test_song_1.title);
    EXPECT_STREQ(test_array.song_array[0].author, test_song_1.author);
    EXPECT_STREQ(test_array.song_array[0].performer, test_song_1.performer);
    EXPECT_EQ(test_array.song_array[0].duration.min, test_song_1.duration.min);
    EXPECT_EQ(test_array.song_array[0].duration.sec, test_song_1.duration.sec);

    Song test_song_2 = {"Title_2", "Author_2", "Performer_2", {2, 22}};
    push_result = push_song(&test_array, test_song_2);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_STREQ(test_array.song_array[1].title, test_song_2.title);
    EXPECT_STREQ(test_array.song_array[1].author, test_song_2.author);
    EXPECT_STREQ(test_array.song_array[1].performer, test_song_2.performer);
    EXPECT_EQ(test_array.song_array[1].duration.min, test_song_2.duration.min);
    EXPECT_EQ(test_array.song_array[1].duration.sec, test_song_2.duration.sec);

    free(test_array.song_array);
}

TEST(PushSongTest, NullPointerTest) {
    bool allocation_result = allocate_memory(nullptr);

    EXPECT_EQ(allocation_result, 1);
}

TEST(ChangingSizeOfArrayTest, SingleChange) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);
    EXPECT_EQ(allocation_result, SUCCESS_FLAG);

    test_array.song_array = change_capacity_of_array(&test_array);
    EXPECT_EQ(test_array.capacity, 2);

    free(test_array.song_array);
}


TEST(ChangingSizeOfArrayTest, DoubleChange) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);
    EXPECT_EQ(allocation_result, SUCCESS_FLAG);

    test_array.song_array = change_capacity_of_array(&test_array);
    test_array.song_array = change_capacity_of_array(&test_array);

    EXPECT_EQ(test_array.capacity, 4);

    free(test_array.song_array);
}


TEST(PrintArrayTest, CorrectDataPrint) {
    Array test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Song test_song = {"Title", "Author", "Performer", {2, 55}};
    bool push_result = push_song(&test_array, test_song);
    EXPECT_EQ(push_result, SUCCESS_FLAG);

    int printing_result = print_array(&test_array, 2);
    EXPECT_EQ(printing_result, 65);

    free(test_array.song_array);
}
