#ifndef PROJECT_INCLUDE_ARRAY_TOOLS_H_
#define PROJECT_INCLUDE_ARRAY_TOOLS_H_

#include <stdbool.h>

/*
typedef struct {
    char* initial_string;
    int length_of_string;
};
*/
typedef struct {
    int count;
    int length;
    char symbol;
} Sequence;

typedef struct {
    int size;
    int capacity;
    Sequence *data;
} Array_of_sequences;

char *get_initial_string(int length);

int get_length_of_string();

bool push_to_array(Array_of_sequences *array, Sequence seq);

Sequence *change_capacity_of_array(Array_of_sequences *array);

bool allocate_memory(Array_of_sequences *array);

int print_array(const Array_of_sequences *array);


#endif  // PROJECT_INCLUDE_ARRAY_TOOLS_H_
