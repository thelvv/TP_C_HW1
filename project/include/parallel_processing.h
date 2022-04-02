#ifndef PROJECT_INCLUDE_PARALLEL_PROCESSING_H_
#define PROJECT_INCLUDE_PARALLEL_PROCESSING_H_

#include <stdbool.h>

#include "array_tools.h"


int start_process(int (*fd)[2], int *pids, char *initial_string, int length, int cpu_core_count);

Array_of_sequences *process_work(int (*fd)[2], int *pids, int cpu_core_count);

Array_of_sequences *count_all_sequences(char *initial_string, int length);

Array_of_sequences *get_combined_array(Array_of_sequences *array_of_sequences);

bool find_sequences(int length);

Array_of_sequences *get_sequences(char *begin_ptr, int step_size);

void free_data(Array_of_sequences *series_array, int i);


#endif  // PROJECT_INCLUDE_PARALLEL_PROCESSING_H_
