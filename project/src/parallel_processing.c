#include <stdio.h>
#include <stdlib.h>
//#include <sys/wait.h>
#include <unistd.h>

#include "parallel_processing.h"


int find_sequences(Array_of_sequences *array, char *initial_string, int length) {
    long cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu_core_count <= 0) {
        return 1;
    }

    printf("%zu\n", cpu_core_count);



    return 0;
}



