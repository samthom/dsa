CFLAGS=-std=c17 -Wall -Wextra -Werror
all:
	gcc hashtable.c -o hashtable $(CFLAGS)	`sdl2-config --cflags --libs`
debug:
	gcc hashtable.c -o hashtable $(CFLAGS)	`sdl2-config --cflags --libs` -DDEBUG
