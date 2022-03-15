#include "../include/song_tools.h"
#include <stdio.h>
#include <stdlib.h>

int scan_num(int *num) {
    char buffer[NAME_STRING_LENGTH], *end;
    if (!scanf("%20s", buffer)) {
        return 1;
    }
    *num = (int) strtol(buffer, &end, 10);
    return 0;
}

int get_duration(Duration *duration) {
    int minutes = -1;
    int seconds = -1;

    if (scan_num(&minutes) | scan_num(&seconds)) {
        printf("Error in getting duration! Try again: ");
        return 1;
    }

    if ((minutes == -1 || seconds == -1) || (minutes > 59 || seconds > 59) || (minutes == 0 && seconds == 0)) {
        return 1;
    }
    while ((getchar()) != '\n');

    duration->min = minutes;
    duration->sec = seconds;

    return 0;
}

int get_song(Song *song) {
    printf("Enter title: ");
    if (song != NULL) {
        if (!scanf("%20s", song->title)) {
            printf("Error in getting title!\n");
            return 1;
        }
        while ((getchar()) != '\n');

        printf("Enter author: ");
        if (!scanf("%20s", song->author)) {
            printf("Error in getting author!\n");
            return 1;
        }
        while ((getchar()) != '\n');

        printf("Enter performer: ");
        if (!scanf("%20s", song->performer)) {
            printf("Error in getting performer!\n");
            return 1;
        }
        while ((getchar()) != '\n');

        printf("Enter duration in format mm ss: ");
        while (get_duration(&song->duration)) {
            printf("Error in getting duration! Try again: ");
        }

        printf("\n");
    }
    return 0;
}

void print_song(const Song *song) {
    printf("Title: %s\n", song->title);
    printf("Author: %s\n", song->author);
    printf("Performer: %s\n", song->performer);
    printf("Duration: %d %d\n\n", song->duration.min, song->duration.sec);
}