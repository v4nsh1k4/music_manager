#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alb.h"   
#include "lib.h"   

void trim(char *s) {
    int len = strlen(s);
    while (len > 0 && s[len-1] == '\n'){ 
        s[len-1]='\0';
         len--;
    }
    while (len > 0 && s[len-1] == ' '){ 
        s[len-1]='\0'; 
        len--;
     }
}

void sep_title_artist(char *line, char *title, char *artist){
    int i = 0;
    int tpos = 0; 
    title[0] = artist[0] = '\0';
    while (line[i] && line[i] != ',' && tpos < 104) {
        title[tpos++] = line[i++];
    }
    title[tpos] = '\0';
    trim(title);
    if (line[i] == ',') i++;
    while (line[i] == ' ') i++;
    int apos = 0;
    while (line[i] && line[i] != '\n' && apos < 104) {
        artist[apos++] = line[i++];}
    artist[apos] = '\0';
    trim(artist);
}

Album* find_album_by_name(Album* head, char* name) {
    while (head){
        if (strcmp(head->name, name)==0) return head;
        head=head->next;
    }
    return NULL;
}

Album* add_album_node(Album* head, char* name) {
    Album* n = malloc(sizeof(Album));
    if (n==NULL) return head;
    strcpy(n->name, name);
    n->songs=NULL;
    n->next=NULL;
    if (head==NULL) return n;
    Album* t = head;
    while (t->next) {
        t = t->next;
        }
    t->next = n;
    return head;
}

void load_one_album_file(Album* a) {
    char filename[220];
    strcpy(filename, a->name);
    strcat(filename, ".txt");
    FILE* file = fopen(filename, "r");
    if (file==NULL) return;
    char line[211];
    while (fgets(line, 211, file)) {
        trim(line);
        if (line[0]=='\0') continue;
        char title[105], artist[105];
        sep_title_artist(line, title, artist);
        Song* s = malloc(sizeof(Song));
        if (!s) continue;
        strcpy(s->title, title);
        strcpy(s->artist, artist);
        s->next = NULL;
        if (!a->songs) a->songs = s;
        else {
            Song* tail = a->songs;
            while (tail->next) tail = tail->next;
            tail->next = s;
        }
    }
    fclose(file);
}

Album* load_albums_from_file(){
    Album* head = NULL;
    FILE* albums = fopen("albums.txt", "r");
    if (!albums) return head;
    char line[211];
    while(fgets(line, 211, albums)){
        trim(line);
        if (!line[0]) continue;
        head = add_album_node(head, line);
        Album* last = head;
        while (last->next) last = last->next;
        load_one_album_file(last);
    }
    fclose(albums);
    return head;
}

void save_albums_to_file(Album* head) {
    Album* a = head;
    while (a){
        char filename[220];
        strcpy(filename, a->name);
        strcat(filename, ".txt");
        FILE* file = fopen(filename, "w");
        if (file) {
            Song* s = a->songs;
            while (s) {
                fprintf(file, "%s, %s\n", s->title, s->artist);
                s = s->next;
            }
            fclose(file);
        }
        a = a->next;
    }
    FILE* albums = fopen("albums.txt", "w");
    if (albums==NULL) return;
    a = head;
    while(a!=NULL){
        fprintf(albums, "%s\n", a->name);
        a =a->next;
    }
    fclose(albums);
}

void add_song_to_album(Album* head, char* album_name, char* song_title, char* song_artist) {
    Album* a = find_album_by_name(head, album_name);
    if (a==NULL){
        head = add_album_node(head, album_name);
        a = find_album_by_name(head, album_name);
    }
    Song* s = malloc(sizeof(Song));
    if (!s) return;
    strcpy(s->title, song_title);
    strcpy(s->artist, song_artist);
    s->next = NULL;
    if (!a->songs) a->songs = s;
    else {
        Song* tail = a->songs;
        while (tail->next) tail = tail->next;
        tail->next =s;
    }
    save_albums_to_file(head);
}

void delete_song_from_album(Album* head, char* album_name, char* song_title) {
    Album* a = find_album_by_name(head, album_name);
    if (a==NULL){
        printf("Album not found.\n"); 
        return; }
    Song* cur = a->songs;
    Song* prev = NULL;
    if (cur && !strcmp(cur->title, song_title)) {
        a->songs = cur->next;
        free(cur);
        save_albums_to_file(head);
        return;
    }

    while (cur && strcmp(cur->title, song_title)) {
        prev = cur;
        cur = cur->next;
    }
    if (cur==NULL){
         printf("Song not found in album.\n"); return; }
    prev->next = cur->next;
    free(cur);
    save_albums_to_file(head);
}

void display_albums(Album* head){
    if (head==NULL) { 
        printf("(No albums)\n"); 
        return; }
    while (head){
        printf("Album: %s\n", head->name);
        Song* s =head->songs;
        int idx = 1;
        while(s){
            printf("  %d) %s - %s\n", idx++, s->title, s->artist);
            s = s->next;
        }
        head=head->next;
    }
}

void free_albums(Album* head) {
    while (head) {
        Song* s = head->songs;
        while (s) {
            Song* ns = s->next;
            free(s);
            s = ns; //ns next song
        }
        Album* na = head->next;
        free(head);
        head=na; //na= next album
    }
}
