#include <gtest/gtest.h>

extern "C" {
#include "array_tools.h"
}

#define SUCCESS_FLAG false

TEST(AllocateMemoryTest, AllocationTest) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.size, 0);
    EXPECT_EQ(test_array.capacity, 1);

    EXPECT_FALSE(test_array.data == nullptr);

    EXPECT_EQ(test_array.data->length, 0);
    EXPECT_EQ(test_array.data->count, 0);


    free(test_array.data);
}

TEST(AllocateMemoryTest, InCorrectInput) {
    bool allocation_result = allocate_memory(NULL);
    EXPECT_EQ(allocation_result, 1);
}


TEST(PushTest, SingleData) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Sequence test_seq = {1, 1, '1'};
    bool push_result = push_to_array(&test_array, test_seq);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.data[0].count, test_seq.count);
    EXPECT_EQ(test_array.data[0].length, test_seq.length);
    EXPECT_EQ(test_array.data[0].symbol, test_seq.symbol);


    free(test_array.data);
}


TEST(PushTest, DoubleData) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Sequence test_seq_1 = {1, 1, '1'};
    bool push_result = push_to_array(&test_array, test_seq_1);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.data[0].count, test_seq_1.count);
    EXPECT_EQ(test_array.data[0].length, test_seq_1.length);
    EXPECT_EQ(test_array.data[0].symbol, test_seq_1.symbol);

    Sequence test_seq_2 = {2, 2, '2'};
    push_result = push_to_array(&test_array, test_seq_2);

    EXPECT_EQ(push_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.data[1].count, test_seq_2.count);
    EXPECT_EQ(test_array.data[1].length, test_seq_2.length);
    EXPECT_EQ(test_array.data[1].symbol, test_seq_2.symbol);

    free(test_array.data);
}

TEST(PushTest, NullPointerTest) {
    bool allocation_result = allocate_memory(nullptr);

    EXPECT_EQ(allocation_result, 1);
}

TEST(ChangingSizeOfArrayTest, SingleChange) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);
    EXPECT_EQ(allocation_result, SUCCESS_FLAG);

    test_array.data = change_capacity_of_array(&test_array);
    EXPECT_EQ(test_array.capacity, 2);

    free(test_array.data);
}


TEST(ChangingSizeOfArrayTest, DoubleChange) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);
    EXPECT_EQ(allocation_result, SUCCESS_FLAG);

    test_array.data = change_capacity_of_array(&test_array);
    test_array.data = change_capacity_of_array(&test_array);

    EXPECT_EQ(test_array.capacity, 4);

    free(test_array.data);
}


TEST(PrintArrayTest, CorrectDataPrint) {
    Array_of_sequences test_array;
    bool allocation_result = allocate_memory(&test_array);

    EXPECT_EQ(allocation_result, SUCCESS_FLAG);
    EXPECT_EQ(test_array.capacity, 1);
    EXPECT_EQ(test_array.size, 0);

    Sequence test_seq = {1, 1, '1'};
    bool push_result = push_to_array(&test_array, test_seq);
    EXPECT_EQ(push_result, SUCCESS_FLAG);

    int printing_result = print_array(&test_array);
    EXPECT_EQ(printing_result, 35);

    free(test_array.data);
}

TEST(PrintArrayTest, InCorrectDataPrint) {
    Array_of_sequences *test_array = NULL;

    int printing_result = print_array(test_array);
    EXPECT_EQ(printing_result, 0);
}


TEST(CharProcessingTest, InCorrectDataPrint) {
    bool result = char_processing(NULL, 5, 1);
    EXPECT_EQ(result, true);
}
