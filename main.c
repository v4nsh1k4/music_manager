#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include "alb.h"
#include "playlist.h"

void trim_string_main(char *s) {
    int i = 0;
    while (s[i] == ' '){
        i++;
    }
    int start = i;
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n'){
        s[len - 1] = '\0';
        len--;
    }
    int end = len - 1;
    while (end >= start && s[end] == ' '){end--;}
    int j = 0;
    while (start <= end){
        s[j++] = s[start++];}
    s[j] = '\0';
}

void log_command(char *text) {
    FILE *logs = fopen("log.txt", "a");
    if (logs == NULL) return;
    fputs(text, logs);
    fputc('\n', logs);
    fclose(logs);
}

void log_int(int x) {
    FILE *logs = fopen("log.txt", "a");
    if (logs == NULL) return;
    char temp[20];
    int pos = 0;
    if (x == 0){
        temp[0] = '0';
        temp[1] = '\0';
    } 
    else{
        char temp[20];
        int k = 0;
        int n = x;
        while (n > 0){
            temp[k] = (n%10) + '0';
            n /=10;
            k++;
        }
        int j = 0;
        while (k > 0){
            k--;
            temp[j++] = temp[k];
        }
        temp[j] = '\0';
    }
    fputs(temp, logs);
    fputc('\n', logs);
    fclose(logs);
}

int main() {
    Song* library= load_song_library();
    Album* albums= load_albums_from_file();
    Playlist* pl = (Playlist*) malloc(sizeof(Playlist));
    pl->head = NULL;
    pl->tail = NULL;
    pl->current = NULL;
     while (1){
        printf("MENU\n1. Library\n2. Albums\n3. Playlist\n4. Log file\n5. Exit\n");
        printf("Select one by typing in the number next to desired specification.\n");
        int c;
        scanf("%d", &c);
        getchar();   //no \n in log file
        log_int(c);
        if (c ==1) {
            printf("Library chosen.\n");
            printf("1. List all songs\n2. List all albums\n");
             int cc;
            scanf("%d", &cc);
            getchar();
            log_int(cc);
            if (cc ==1){
                display_library(library);
            }
            else if (cc ==2){
                display_albums(albums);
            }
            else printf("Error!\n");
        }
        else if(c ==2){
            printf("Albums chosen.\n");
            printf("1. View an album\n2. Add songs to an album\n3. Delete songs from an album\n");
            int cc;
            scanf("%d", &cc);
            getchar();
            log_int(cc);
            if(cc ==1){
                 printf("Enter album name:\n");
                char album_name[105];
                fgets(album_name, 105, stdin);
                trim_string_main(album_name);
                log_command(album_name);
                Album* a = find_album_by_name(albums, album_name);
                if(a == NULL){
                    printf("Album not found.\n");
                } 
                else{
                    printf("Album: %s\n", a->name);
                    Song* s = a->songs;
                    int i = 1;
                    while (s != NULL) {
                        printf("  %d) %s - %s\n", i, s->title, s->artist);
                        s = s->next;
                        i++;
                    }
                }
            }
            else if(cc ==2){
                char album_name[105];
                char songname[105];
                printf("Enter album name:\n");
                fgets(album_name, 105, stdin);
                trim_string_main(album_name);
                log_command(album_name);
                printf("Enter song name:\n");
                fgets(songname, 105, stdin);
                trim_string_main(songname);
                log_command(songname);
                Song* p = library;
                char found_artist[105];
                int exist =0;
                while (p != NULL){
                    if (strcmp(p->title, songname) ==0) {
                        strcpy(found_artist, p->artist);
                        exist = 1;
                        break;
                    }
                    p = p->next;
                }
                if(exist==0){
                    printf("Song does not exist in library.\n");
                } 
                 else {
                    add_song_to_album(albums, album_name, songname, found_artist);
                    albums = load_albums_from_file();
                    printf("Song added to album.\n");
                }
            }
            else if (cc ==3) {
                char album_name[105];
                char songname[105];
                printf("Enter album name:\n");
                fgets(album_name, 105, stdin);
                trim_string_main(album_name);
                log_command(album_name);
                printf("Enter song name:\n");
                fgets(songname, 105, stdin);
                trim_string_main(songname);
                log_command(songname);
                delete_song_from_album(albums, album_name, songname);
                albums = load_albums_from_file();
            }
            else {
                printf("Error!\n");
            }
        }
        else if(c ==3){
            printf("Playlist chosen.\n");
            printf("1. Add song\n2. Remove song\n3. Play next song\n4. Play previous song\n5. Add album to playlist\n6. View playlist\n");
            int cc;
            scanf("%d", &cc);
            getchar();
            log_int(cc);
            if (cc ==1) {
                printf("Enter song name:\n");
                char name[105];
                fgets(name, 105, stdin);
                trim_string_main(name);
                log_command(name);
                Song* p = library;
                while(p !=NULL){
                    if (strcmp(p->title, name) == 0) break;
                    p = p->next;
                }
                if(p ==NULL){ 
                    printf("Song not found in library.\n");}
                else{
                    add_song_playlist(pl, p);
                    printf("Added to playlist.\n");
                }
            }
            else if(cc ==2){
                printf("Enter song name:\n");
                char name[105];
                fgets(name, 105, stdin);
                trim_string_main(name);
                log_command(name);
                remove_song_playlist(pl, name);
            }
            else if(cc ==3){
                play_next(pl);
            }
            else if(cc ==4){
                play_prev(pl);
            }
            else if(cc ==5){
                printf("Enter album name:\n");
                char name[105];
                fgets(name, 105, stdin);
                trim_string_main(name);
                log_command(name);
                add_album_to_playlist(pl, albums, name);
            }
            else if(cc ==6){
                show_playlist(pl);
            }
            else printf("Error!\n");
        }

        else if(c ==4){
            printf("***LOG FILE CONTENT***\n");
            FILE* f = fopen("log.txt", "r");
            if(f == NULL){
                printf("(No log file yet)\n");
            } 
            else {
                char line[211];
                while (fgets(line, 211, f)!= NULL){
                    printf("%s", line);
                }
                fclose(f);
            }

            printf("*************************\n");
        }
        else if(c ==5){
            break;
        }
        else {
            printf("Error!\n");
        }
    }
    return 0;
}
