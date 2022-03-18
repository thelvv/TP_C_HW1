#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/array_tools.h"


#define INITIAL_ARR_SIZE 0
#define INITIAL_ARR_CAPACITY 1
#define ARR_CAPACITY_COEFF 2
#define PRINT_ALL_SONGS 1
#define PRINT_SPEC_SONGS 2

#define CONTINUE_ANS 1
#define STOP_ANS 0


int push_song(Array *array, Song song) {
    if (array->size >= array->capacity) {
        array->song_array = change_capacity_of_array(array);
        if (!array->song_array) {
            return 1;
        }
    }
    int current_size = array->size;
    array->song_array[current_size] = song;
    array->size++;

    return 0;
}

Song *change_capacity_of_array(Array *array) {
    if (array == NULL) {
        return NULL;
    }
    int new_capacity = array->capacity * ARR_CAPACITY_COEFF;

    Song *new_song_array = calloc(new_capacity, sizeof(Song));
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
    if (array == NULL) {
        return 1;
    }

    Song *new_song_array = calloc(1, sizeof(Song));
    if (!new_song_array) {
        free(new_song_array);
        return 1;
    }

    array->song_array = new_song_array;
    array->capacity = INITIAL_ARR_CAPACITY;
    array->size = INITIAL_ARR_SIZE;

    return 0;
}


int print_array(const Array *array, int flag) {
    int num_of_chars = 0;
    int last_num = 0;
    if (flag == PRINT_ALL_SONGS) {
        for (int i = 0; i < array->size; ++i) {
            num_of_chars += print_song(&array->song_array[i]);
            if (num_of_chars == last_num) {
                printf("Error!");
                return 0;
            }
            last_num = num_of_chars;
        }
        return num_of_chars;
    }

    if (flag == PRINT_SPEC_SONGS) {
        for (int i = 0; i < array->size; ++i) {
            if (!strcmp(*(&array->song_array[i].performer), *(&array->song_array[i].author))) {
                num_of_chars += print_song(&array->song_array[i]);
                if (num_of_chars == last_num) {
                    printf("Error!");
                    return 0;
                }
                last_num = num_of_chars;
            }
        }
        return num_of_chars;
    }
    return num_of_chars;
}

int next_step() {
    int answer = 0;
    printf("Type 1 to continue. Type 0 to stop: ");

    if (scan_num(&answer)) {
        printf("Error in getting answer!\n");
        return -1;
    }

    if (answer == CONTINUE_ANS || answer == STOP_ANS) {
        return answer;
    } else {
        printf("Error! Incorrect input!\n");
        return -1;
    }
}
