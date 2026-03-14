#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h" 

void trim_in_lib(char *s) {
    int len=strlen(s);
    while (len > 0 && s[len-1] == '\n'){ 
         s[len-1] = '\0'; len--; 
    }
    while(len > 0 && s[len-1] == ' '){ 
        s[len-1] = '\0'; len--;
    }
}

void sep_songinfo_line(char *line, char *title, char *artist){
    int i = 0, tpos = 0;
    title[0] = '\0';
    artist[0] = '\0';
    while (line[i] && line[i] != ',' && tpos < 104){
        title[tpos++] = line[i++];}
    title[tpos] = '\0';
    trim_in_lib(title);
    if (line[i] == ',') i++;
    while (line[i] == ' ') i++;
    int apos = 0;
    while (line[i] && line[i] != '\n' && apos < 104){
        artist[apos++] = line[i++];}
    artist[apos] = '\0';
    trim_in_lib(artist);
}

Song* load_song_library(){
    FILE *songs = fopen("songs.txt", "r");
    if (!songs) return NULL;
    char line[211];
    Song *head = NULL, *tail = NULL;
    while (fgets(line, 211, songs)) {
        if (line[0] == '\n' || line[0] == '\0') continue;
        char title[105], artist[105];
        sep_songinfo_line(line, title, artist);
        Song *n = malloc(sizeof(Song));
        if (!n) continue;
        strcpy(n->title, title);
        strcpy(n->artist, artist);
        n->next = NULL;
        if (!head) head = tail = n;
        else {
             tail->next = n; tail = n; 
            }
    }
    fclose(songs);
    return head;
}

void display_library(Song* head) {
    Song *p =head;
    int index = 1;
    if (p==NULL) { 
        printf("  Library empty\n"); return; 
    }
    while(p!=NULL){
        printf("  %d) %s - %s\n", index++, p->title, p->artist);
        p=p->next;
    }
}

void free_library(Song* head) {
    while (head) {
        Song *t = head;
        head = head->next;
        free(t);
    }
}
