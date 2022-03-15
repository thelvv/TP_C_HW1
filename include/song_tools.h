#ifndef HW1_SONG_TOOLS_H
#define HW1_SONG_TOOLS_H

#define NAME_STRING_LENGTH 20

typedef struct duration {
    int min;
    int sec;
} Duration;

typedef struct song {
    char title[NAME_STRING_LENGTH];
    char author[NAME_STRING_LENGTH];
    char performer[NAME_STRING_LENGTH];
    Duration duration;
} Song;

int scan_num(int *num);

int get_duration(Duration *duration);

int get_song(Song *song);

void print_song(const Song *song);


#endif //HW1_SONG_TOOLS_H
