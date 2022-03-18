#include "song_tools.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SONG_DURATION 59

int scan_num(int *num) {
    char buffer[NAME_STRING_LENGTH] = "";
    char *end = NULL;
    if (!scanf("%19s", buffer)) {
        return 1;
    }
    *num = (int) strtol(buffer, &end, 10);
    return 0;
}

int get_duration(Duration *duration) {
    if (duration == NULL) {
        return 1;
    }

    int minutes = -1;
    int seconds = -1;

    if (scan_num(&minutes) | scan_num(&seconds)) {
        printf("Error in getting duration! Try again: ");
        return 1;
    }

    if ((minutes == -1 || seconds == -1) || (minutes > MAX_SONG_DURATION || seconds > 59) ||
        (minutes == 0 && seconds == 0)) {
        return 1;
    }
    while ((getchar()) != '\n') {}

    duration->min = minutes;
    duration->sec = seconds;

    return 0;
}

int get_song(Song *song) {
    if (song == NULL) {
        return 1;
    }

    printf("Enter title: ");

    if (!scanf("%19s", song->title)) {
        printf("Error in getting title!\n");
        return 1;
    }
    while ((getchar()) != '\n') {}

    printf("Enter author: ");
    if (!scanf("%19s", song->author)) {
        printf("Error in getting author!\n");
        return 1;
    }
    while ((getchar()) != '\n') {}

    printf("Enter performer: ");
    if (!scanf("%19s", song->performer)) {
        printf("Error in getting performer!\n");
        return 1;
    }
    while ((getchar()) != '\n') {}

    printf("Enter duration in format mm ss: ");
    while (get_duration(&song->duration)) {
        printf("Error in getting duration! Try again: ");


        printf("\n");
    }

    return 0;
}

int print_song(const Song *song) {
    if (song == NULL) {
        return 0;
    }

    int num_of_chars = printf("Title: %s\n", song->title);
    num_of_chars += printf("Author: %s\n", song->author);
    num_of_chars += printf("Performer: %s\n", song->performer);
    num_of_chars += printf("Duration: %d %d\n\n", song->duration.min, song->duration.sec);
    return num_of_chars;
}
