#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "playlist.h"
#include "alb.h"   

void add_song_playlist(Playlist* pl, Song* s) {
    if (s ==NULL) return;
    PNode* n = (PNode*) malloc(sizeof(PNode));
    if (n ==NULL) return;
    n->song =s;
    n->next =NULL;
    n->prev =NULL;
    if (pl->head ==NULL){
        pl->head = pl->tail = pl->current = n;
        n->next = n;
        n->prev = n;
        return;
    }
    n->next =pl->head;
    n->prev =pl->tail;
    pl->tail->next =n;
    pl->head->prev =n;
    pl->tail =n;
}

void remove_song_playlist(Playlist* pl, char* title) {
    if (pl->head ==NULL) return;
    PNode* p=pl->head;
    do{
     if(strcmp(p->song->title, title)==0){
            if(p->next ==p && p->prev ==p){
                free(p);
                pl->head =pl->tail =pl->current = NULL;
                return;
            }
            p->prev->next =p->next;
            p->next->prev =p->prev;
            if (pl->head ==p)pl->head = p->next;
            if (pl->tail ==p)pl->tail = p->prev;
            if (pl->current ==p)pl->current = p->next;
            free(p);
            return;
        }
        p = p->next;
    } 
    while (p != pl->head);
}

void add_album_to_playlist(Playlist* pl, Album* albums, char* name){
    Album* a = albums;
    while (a != NULL) {
        if (strcmp(a->name, name)==0){
            Song* s=a->songs;
            while (s!=NULL){
                add_song_playlist(pl, s);
                s=s->next;
            }
             return;
        }
        a=a->next;
    }
    printf("Album not found.\n");
}

void play_next(Playlist* pl){
    if (pl->current == NULL) {
        printf("Playlist empty.\n");
        return;
    }
    pl->current = pl->current->next;
    printf("Now playing: %s - %s\n",
           pl->current->song->title,
           pl->current->song->artist);
 }

void play_prev(Playlist* pl) {
    if (pl->current==NULL){
        printf("Playlist empty.\n");
        return;
    }
    pl->current = pl->current->prev;
    printf("Now playing: %s - %s\n",
           pl->current->song->title,
           pl->current->song->artist);
}
void show_playlist(Playlist* pl){
    if (pl->head == NULL){
        printf("Playlist empty.\n");
        return;
    }
    PNode* p=pl->head;
    do{
        printf("%s - %s\n", p->song->title, p->song->artist);
         p=p->next;
    } 
    while (p!=pl->head);
}

void free_playlist(Playlist* pl) {
    if (pl->head==NULL){
        free(pl);
        return;
    }
    PNode* cur=pl->head->next;
    while(cur!=pl->head){
        PNode* next=cur->next;
        free(cur);
        cur=next;
    }
    free(pl->head);
    free(pl);
}
