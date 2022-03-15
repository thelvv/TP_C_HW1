#include <stdio.h>
#include <stdlib.h>
#include "../include/array_tools.h"


int main() {
    Array array;
    if (allocate_memory(&array)) {
        free(array.song_array);
        return 1;
    }

    Song song;

    do {
        printf("Type 1 to enter new data; type 2 to print all songs; type 3 to print songs with equal author and performer: ");
        int answer = 0;
        if (scan_num(&answer)) {
            printf("Error!\n");
        }

        switch (answer) {
            case 1:
                get_song(&song);
                push_song(&array, song);
                break;
            case 2:
                if (array.size == 0) {
                    printf("Error! Array is empty!.\n");
                    break;
                }

                print_array(&array, 1);
                break;
            case 3:
                if (array.size == 0) {
                    printf("Error! Array is empty!.\n");
                    break;
                }

                if (print_array(&array, 2)) {
                    printf("Error! Required songs not found!");
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
