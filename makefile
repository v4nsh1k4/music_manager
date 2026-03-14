CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = main.o alb.o lib.o playlist.o

all: music_app

music_app: $(OBJ)
	$(CC) $(CFLAGS) -o music_app $(OBJ)

main.o: main.c alb.h lib.h playlist.h
alb.o: alb.c alb.h lib.h
lib.o: lib.c lib.h
playlist.o: playlist.c playlist.h lib.h alb.h

clean:
	rm -f *.o music_app
