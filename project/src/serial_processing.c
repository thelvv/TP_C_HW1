#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "serial_processing.h"

#define FILENAME "../input.txt"


bool find_sequences(int length) {
    if (length < 1) {
        return 1;
    }

    Array_of_sequences array;
    if (allocate_memory(&array)) {
        free(array.data);
        return 1;
    }

    char *initial_string = get_initial_string(length);
    if (initial_string == NULL) {
        return -1;
    }

    int count = 0;
    char sym, previous_sym = initial_string[0];
    for (int i = 0; i < length; ++i) {
        sym = initial_string[i];
        // printf("%c\n", sym);

        if (sym == previous_sym) {
            ++count;
        } else {
            if (count > 1) {
                char_processing(&array, previous_sym, count);
            }
            count = 1;
        }

        previous_sym = sym;
    }

    print_array(&array);
    print_spec_seq(&array);

    free(array.data);
    free(initial_string);

    return 0;
}


int print_spec_seq(const Array_of_sequences *array) {
    Sequence *seq = get_most_frequent_seq(array);
    if (seq != NULL) {
        print_seq(seq);
        return 0;
    } else {
        printf("Error!");
        return 1;
    }
}
