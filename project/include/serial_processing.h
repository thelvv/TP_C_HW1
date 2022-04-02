#ifndef PROJECT_INCLUDE_SERIAL_PROCESSING_H_
#define PROJECT_INCLUDE_SERIAL_PROCESSING_H_

#define FILENAME "../input.txt"

#include <stdbool.h>

#include "array_tools.h"

bool find_sequences(int length);

int print_spec_seq(const Array_of_sequences *array);


#endif  // PROJECT_INCLUDE_SERIAL_PROCESSING_H_
