#ifndef HW1_ARRAY_TOOLS_H
#define HW1_ARRAY_TOOLS_H
#include "song_tools.h"

typedef struct song_array {
    Song *song_array;
    int capacity;
    int size;
} Array;


int push_song(Array *array, Song song);

Song *change_size_of_array(Array *array);

int allocate_memory(Array *array);

int print_array(const Array *array, int flag);

int next_step();


#endif //HW1_ARRAY_TOOLS_H
