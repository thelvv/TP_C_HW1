#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_tools.h"

#define INITIAL_ARR_SIZE 0
#define INITIAL_ARR_CAPACITY 1
#define ARR_CAPACITY_COEFF 2


#define FILENAME "../input.txt"

char *get_initial_string(int length) {
    char *initial_string = calloc(length, sizeof(char));

    if (!initial_string) {
        free(initial_string);
        return NULL;
    }

    FILE *file = fopen(FILENAME, "r+");
    if (!file) {
        fclose(file);
        return NULL;
    }
    fscanf(file, "%s", initial_string);

    fclose(file);
    return initial_string;
}


int get_length_of_string() {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        fclose(file);
        return -1;
    }

    char sym = ' ';
    int length = 0;
    do {
        fscanf(file, "%c", &sym);
        ++length;
    } while (sym != '\n');

    fclose(file);
    return length;
}


bool push_to_array(Array_of_sequences *array, Sequence seq) {
    if (array->size >= array->capacity) {
        array->data = change_capacity_of_array(array);
        if (!array->data) {
            return true;
        }
    }
    int current_size = array->size;
    array->data[current_size] = seq;
    array->size++;

    return false;
}

Sequence *change_capacity_of_array(Array_of_sequences *array) {
    if (array == NULL) {
        return NULL;
    }
    int new_capacity = array->capacity * ARR_CAPACITY_COEFF;

    Sequence *new_array = calloc(new_capacity, sizeof(Sequence));
    if (!new_array) {
        free(new_array);
        return NULL;
    }

    memcpy(new_array, array->data, sizeof(Sequence) * array->size);
    free(array->data);

    array->capacity = new_capacity;

    return new_array;
}

bool allocate_memory(Array_of_sequences *array) {
    if (array == NULL) {
        return true;
    }

    Sequence *new_array = calloc(1, sizeof(Sequence));
    if (!new_array) {
        free(new_array);
        return true;
    }

    array->data = new_array;
    array->capacity = INITIAL_ARR_CAPACITY;
    array->size = INITIAL_ARR_SIZE;

    return false;
}


int print_array(const Array_of_sequences *array) {
    for (int i = 0; i < array->size; ++i) {
        printf("%d: Symbol: %c; Length: %d; Count: %d;\n", i, array->data[i].symbol, array->data[i].length,
               array->data[i].count);
    }
    //printf("\n");
    return 0;
}

