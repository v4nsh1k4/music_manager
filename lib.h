#ifndef LIB_H
#define LIB_H

typedef struct Song {
    char title[105];
    char artist[105];
    struct Song* next;
} Song;

typedef struct Album Album;

Song* load_song_library();
void display_library(Song* head);
void free_library(Song* head);

#endif
