#include "../include/array_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int push_song(Array *array, Song song) {
    if (array->size >= array->capacity) {
        array->song_array = change_size_of_array(array);
        if (!array->song_array) {
            return 1;
        }
    }
    int current_size = array->size;
    array->song_array[current_size] = song;
    array->size++;

    return 0;
}

Song *change_size_of_array(Array *array) {
    int new_capacity = array->capacity * 2;

    Song *new_song_array = calloc(new_capacity, sizeof(int));
    if (!new_song_array) {
        free(new_song_array);
        return NULL;
    }
    memcpy(new_song_array, array->song_array, sizeof(Song) * array->size);
    free(array->song_array);

    array->capacity = new_capacity;

    return new_song_array;
}

int allocate_memory(Array *array) {
    Song *new_song_array = calloc(1, sizeof(Song));
    if (!new_song_array) {
        free(new_song_array);
        return 1;
    }

    array->song_array = new_song_array;
    array->capacity = 1;
    array->size = 0;

    return 0;
}


int print_array(const Array *array, int flag) {
    if (flag == 1) {
        for (int i = 0; i < array->size; ++i) {
            print_song(&array->song_array[i]);
        }
        return 0;
    }

    if (flag == 2) {
        for (int i = 0; i < array->size; ++i) {
            if (!strcmp(*(&array->song_array[i].performer), *(&array->song_array[i].author))) {
                print_song(&array->song_array[i]);
                flag = 0;
            }
        }
        return flag;
    }
    return 0;
}

int next_step() {
    int answer = 0;
    printf("Type 1 to continue. Type 0 to stop: ");

    if (scan_num(&answer)) {
        printf("Error in getting answer!\n");
        return -1;
    }

    if (answer == 1 || answer == 0) {
        return answer;
    } else {
        printf("Error! Incorrect input!\n");
        return -1;
    }
}