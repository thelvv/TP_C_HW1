#ifndef PROJECT_INCLUDE_SONG_TOOLS_H_
#define PROJECT_INCLUDE_SONG_TOOLS_H_

#include <stdbool.h>

#define NAME_STRING_LENGTH 20

typedef struct {
    int min;
    int sec;
} Duration;

typedef struct {
    char title[NAME_STRING_LENGTH];
    char author[NAME_STRING_LENGTH];
    char performer[NAME_STRING_LENGTH];
    Duration duration;
} Song;

bool scan_num(int *num);

bool get_duration(Duration *duration);

bool get_song(Song *song);

int print_song(const Song *song);


#endif  // PROJECT_INCLUDE_SONG_TOOLS_H_
