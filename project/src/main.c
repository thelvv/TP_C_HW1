#include <stdlib.h>

#include "array_tools.h"
#include "serial_processing.h"
#include "parallel_processing.h"



/*
Федоров А.А. Web-11
Вариант #16
Сравните и выведите в консоль время работы последовательного и параллельного с использованием нескольких процессов
алгоритмов, каждый из которых выделяет в динамической памяти символьный массив размером 100 Мб и подсчитывает количество
серий повторяющихся символов разной длины, после чего выводит представителя серии самой часто встречаемой длины.
*/



int main() {
    int length_of_string = get_length_of_string();

    Array_of_sequences array;
    if (allocate_memory(&array)) {
        free(array.data);
        return 1;
    }

    find_sequences(length_of_string);

    return 0;
}
