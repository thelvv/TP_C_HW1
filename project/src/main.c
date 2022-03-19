#include <stdio.h>
#include <stdlib.h>

#include "song_tools.h"
#include "array_tools.h"

/*
 Федоров А.А. Web-11
 Вариант #16
 Создать структуру для хранения информации о музыкальной композиции:
 ее авторе, исполнителе, названии и длительности.
 Составить с ее использованием программу вывода информации обо всех песнях, исполненных своим автором.
*/

#define GET_NEW_SONG 1
#define PRINT_ALL_SONGS 2
#define PRINT_SPEC_SONGS 3




int main() {
    Array array;
    if (allocate_memory(&array)) {
        free(array.song_array);
        return 1;
    }

    Song new_song;

    do {
        printf("Type 1 to enter new data; type 2 to print all songs; type 3 to print songs with equal author and performer: ");
        int answer = 0;
        if (scan_num(&answer)) {
            printf("Error!\n");
        }
        printf("\n");

        switch (answer) {
            case GET_NEW_SONG:
                get_song(&new_song);
                push_song(&array, new_song);
                break;
            case PRINT_ALL_SONGS:
                if (array.size == 0) {
                    printf("Error! Array is empty!\n");
                    break;
                }

                print_array(&array, PRINT_ALL_SONGS);
                break;
            case PRINT_SPEC_SONGS:
                if (array.size == 0) {
                    printf("Error! Array is empty!\n");
                    break;
                }

                if (!print_array(&array, PRINT_SPEC_SONGS)) {
                    printf("Error! Required songs not found!\n");
                }
                break;

            default:
                printf("Error!\n");
                next_step();
                break;
        }
    } while (next_step());

    free(array.song_array);

    return 0;
}
