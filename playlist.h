#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "lib.h"
typedef struct Album Album;

typedef struct PNode {
    Song* song;
    struct PNode* next;
    struct PNode* prev;
} PNode;

typedef struct Playlist {
    PNode* head;
    PNode* tail;
    PNode* current;
} Playlist;


void add_song_playlist(Playlist* pl, Song* s);
void remove_song_playlist(Playlist* pl, char* title);
void add_album_to_playlist(Playlist* pl, Album* albums, char* name);
void play_next(Playlist* pl);
void play_prev(Playlist* pl);
void show_playlist(Playlist* pl);
void free_playlist(Playlist* pl); //wasnt workign

#endif
