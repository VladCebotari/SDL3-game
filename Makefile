#-ggdb debug //  -02 -DNDEBUG  fara debug si 02 lvl de optimizare(este si 03 care poate fi mai rapid)
#CFLAGS = $(shell pkg-config --cflags sdl3 sdl3-image) -02 -DNDEBUG
CC = g++

CFLAGS = -ggdb -Wall $(shell pkg-config --cflags sdl3 sdl3-image) 
LIBS = $(shell pkg-config --libs sdl3 sdl3-image)
SRC = src/main.cpp src/player.cpp


all: sdltutorial 

sdltutorial:  $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o output

clean:
	rm output
	
	
	
	
	
