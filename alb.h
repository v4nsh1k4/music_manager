#ifndef ALB_H
#define ALB_H
#include "lib.h" //cuase we need song

typedef struct Album {
    char name[105];
    Song* songs;
    struct Album* next;
} Album;

Album* load_albums_from_file();
void save_albums_to_file(Album* head);
Album* find_album_by_name(Album* head, char* name);
Album* add_album_node(Album* head, char* name);
void add_song_to_album(Album* head, char* album_name, char* song_title, char* song_artist);
void delete_song_from_album(Album* head, char* album_name, char* song_title);
void display_albums(Album* head);
void free_albums(Album* head); // seg fault fixed

#endif
