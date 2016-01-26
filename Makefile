all: game

game: game.cpp
	g++ game.cpp -lSDL2_mixer -lSDL2_image `sdl2-config --cflags --static-libs`

