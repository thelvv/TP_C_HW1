#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "parallel_processing.h"


bool find_sequences(int length) {
    if (length < 1) {
        return 1;
    }
    char *initial_string = get_initial_string(length);
    if (initial_string == NULL) {
        return 1;
    }
    int cpu_core_count = (int) sysconf(_SC_NPROCESSORS_ONLN);

    Array_of_sequences *array_of_sequences = count_all_sequences(initial_string, length);
    if (array_of_sequences == NULL) {
        return 1;
    }

    Array_of_sequences *combined_array_of_sequences = get_combined_array(array_of_sequences);
    if (combined_array_of_sequences == NULL) {
        for (int i = 0; i < cpu_core_count; ++i) {
            free(array_of_sequences[i].data);
        }
        free(array_of_sequences);
        return 1;
    }

    Sequence *most_frequent_series = get_most_frequent_seq(combined_array_of_sequences);
    if (most_frequent_series == NULL) {
        for (int i = 0; i < cpu_core_count; ++i) {
            free(array_of_sequences[i].data);
        }

        free(array_of_sequences);
        free(combined_array_of_sequences->data);
        free(combined_array_of_sequences);

        return 1;
    }

    // print_seq(most_frequent_series);

    for (int i = 0; i < cpu_core_count; ++i) {
        free(array_of_sequences[i].data);
    }

    free(array_of_sequences);
    free(combined_array_of_sequences->data);
    free(combined_array_of_sequences);

    return 0;
}


Array_of_sequences *count_all_sequences(char *initial_string, int length) {
    if (initial_string == NULL) {
        return NULL;
    }
    if (length < 1) {
        return NULL;
    }

    int cpu_core_count = (int) sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu_core_count <= 0) {
        return NULL;
    }

    int(*fd)[2] = (int (*)[2]) malloc(cpu_core_count * sizeof(int[2]));
    pid_t *pids = (int *) malloc(cpu_core_count * sizeof(int));

    if (!fd || !pids) {
        if (pids) {
            free(pids);
        }

        if (fd) {
            free(fd);
        }

        return NULL;
    }

    int result = start_process(fd, pids, initial_string, length, cpu_core_count);

    if (result != 0) {
        free(fd);
        free(pids);
        return NULL;
    }

    Array_of_sequences *array_of_sequences = process_work(fd, pids, cpu_core_count);
    free(fd);
    free(pids);

    return array_of_sequences;
}


int start_process(int (*fd)[2], int *pids, char *initial_string, int length, int cpu_core_count) {
    if (length < 1) {
        return 1;
    }
    int step_length = length / cpu_core_count;
    char *begin_ptr = initial_string;

    for (int i = 0; i < cpu_core_count; ++i) {
        if (pipe(fd[i]) == -1) {
            return -1;
        }
        pids[i] = fork();
        if (pids[i] == -1) {
            return -1;
        } else if (pids[i] == 0) {
            begin_ptr = begin_ptr + step_length * i;

            if (i == cpu_core_count - 1) {
                step_length = initial_string + length - begin_ptr;
            }
            close(fd[i][0]);

            Array_of_sequences *array_of_sequences = get_sequences(begin_ptr, step_length);
            // print_array(array_of_sequences);

            if (array_of_sequences == NULL) {
                free(fd);
                free(pids);
                exit(1);
            }

            int size_of_arr = array_of_sequences->size * sizeof(Sequence);
            int result = 0;
            result += write(fd[i][1], (char *) array_of_sequences, sizeof(Array_of_sequences));
            result += write(fd[i][1], (char *) array_of_sequences->data, size_of_arr);
            close(fd[i][1]);

            free(array_of_sequences->data);
            free(fd);
            free(pids);

            if (result == size_of_arr) {
                exit(0);
            } else {
                exit(1);
            }
        }
        close(fd[i][1]);
    }
    return 0;
}


Array_of_sequences *process_work(int (*fd)[2], int *pids, int cpu_core_count) {
    Array_of_sequences *array_of_sequences = (Array_of_sequences *) malloc(sizeof(Array_of_sequences) * cpu_core_count);
    if (array_of_sequences == NULL) {
        return NULL;
    }

    for (int i = 0; i < cpu_core_count; ++i) {
        int status = 0;
        waitpid(pids[i], &status, 0);

        if ((status != 0)) {
            free_data(array_of_sequences, i);
            return NULL;
        }

        int result = read(fd[i][0], (char *) &array_of_sequences[i], sizeof(Array_of_sequences));
        if (result != sizeof(Array_of_sequences)) {
            return NULL;
        }

        int size_of_data = array_of_sequences[i].size * sizeof(Sequence);
        Sequence *series = (Sequence *) malloc(size_of_data);

        if (series == NULL) {
            free_data(array_of_sequences, i);
            return NULL;
        }

        result = read(fd[i][0], (char *) series, size_of_data);
        array_of_sequences[i].data = series;
        if (result != size_of_data) {
            free_data(array_of_sequences, i);
            return NULL;
        }
        close(fd[i][0]);
    }

    return array_of_sequences;
}


Array_of_sequences *get_combined_array(Array_of_sequences *array_of_sequences) {
    int cpu_core_count = (int) sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu_core_count <= 0) {
        return NULL;
    }
    int total_length = 0;

    for (int i = 0; i < cpu_core_count; ++i) {
        total_length += array_of_sequences[i].capacity;
    }

    Array_of_sequences *result_array = (Array_of_sequences *) malloc(sizeof(Array_of_sequences));
    Sequence *result_series = (Sequence *) malloc(sizeof(Sequence) * total_length);

    if (!result_array || !result_series) {
        if (result_series) {
            free(result_series);
        }

        if (result_array) {
            free(result_array);
        }

        return NULL;
    }

    result_array->data = result_series;
    result_array->capacity = total_length;
    result_array->size = 0;

    if (total_length == cpu_core_count) {
        char_processing(result_array, array_of_sequences[0].data[0].symbol,
                        array_of_sequences[0].data[0].length);

        for (int i = 1; i < cpu_core_count; ++i) {
            result_array->data[0].length += array_of_sequences[i].data[0].length;
        }
    } else {
        for (int i = 0; i < cpu_core_count; ++i) {
            for (int j = 0; j < array_of_sequences[i].size; ++j) {
                char_processing(result_array, array_of_sequences[i].data[j].symbol,
                                array_of_sequences[i].data[j].length);
            }
        }
    }
    return result_array;
}


void free_data(Array_of_sequences *array_of_sequences, int i) {
    for (int j = 0; j < i; ++j) {
        free(array_of_sequences[j].data);
    }
    free(array_of_sequences);
}


Array_of_sequences *get_sequences(char *begin_ptr, int step_size) {
    Array_of_sequences *array = NULL;
    if (allocate_memory(array)) {
        free(array);
        return NULL;
    }

    int count = 0;
    char sym, previous_sym = begin_ptr[0];
    for (int i = 0; i < step_size; ++i) {
        sym = begin_ptr[i];

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
    return array;
}
