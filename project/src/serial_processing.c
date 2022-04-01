#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "array_tools.h"
#include "serial_processing.h"


int find_sequences(Array_of_sequences *array, int length) {
    char* initial_string = get_initial_string(length);
    if (initial_string == NULL) {
        return -1;
    }

    int count = 0;
    char sym, previous_sym = initial_string[0];
    for (int i = 0; i < length; ++i) {
        sym = initial_string[i];
        //printf("%c\n", sym);

        if (sym == previous_sym) {
            ++count;
        } else {
            if (count > 1) {
                char_processing(array, previous_sym, count);
            }
            count = 1;
        }

        previous_sym = sym;
    }

    print_array(array);
    print_spec_seq(array);

    free(initial_string);

    return 0;
}


int get_num_of_record(const Array_of_sequences *array, char ch, int count) {
    for (int i = 0; i < array->size; ++i) {
        if ((array->data[i].symbol == ch) && (array->data[i].length == count)) {
            return i;
        }
    }

    return -1;
}

int char_processing(Array_of_sequences *array, char ch, int count) {
    int num_of_record = get_num_of_record(array, ch, count);
    if (num_of_record == -1) {
        Sequence seq = {1, count, ch};
        if (push_to_array(array, seq)) {
            printf("Error in pushing new element to array!\n");
            return -1;
        }
    } else {
        ++array->data[num_of_record].count;

    }
    //print_array(array);

    return 0;
}

int print_seq(const Sequence *seq) {
    printf("Symbol: %c; Length: %d; Count: %d;\n", seq->symbol, seq->length, seq->count);

    for (int i = 0; i < seq->length; ++i) {
        printf("%c", seq->symbol);
    }
    printf("\n");

    return 0;
}

Sequence *get_most_frequent_seq(const Array_of_sequences *array) {
    int max = 0;
    int num_of_max = -1;
    for (int i = 0; i < array->size; ++i) {
        if (array->data[i].count > max) {
            max = array->data[i].length;
            num_of_max = i;
        }
    }
    if (num_of_max != -1) {
        return &array->data[num_of_max];
    }
    return NULL;
}

void print_spec_seq(const Array_of_sequences *array) {
    Sequence *seq = get_most_frequent_seq(array);
    if (seq != NULL) {
        print_seq(seq);
    } else {
        printf("Error!");
    }
}
