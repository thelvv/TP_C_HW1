#ifndef PROJECT_INCLUDE_SERIAL_PROCESSING_H
#define PROJECT_INCLUDE_SERIAL_PROCESSING_H

#define FILENAME "../input.txt"


int find_sequences(Array_of_sequences *array, int length);

int get_num_of_record(const Array_of_sequences *array, char ch, int count);

int char_processing(Array_of_sequences *array, char ch, int count);

Sequence *get_most_frequent_seq(const Array_of_sequences *array);

void print_spec_seq(const Array_of_sequences *array);


#endif  // PROJECT_INCLUDE_SERIAL_PROCESSING_H
