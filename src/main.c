
/*
 * main.c - The main C execution source file
 */

#include "include/event.h"
#include "include/game.h"
#include "include/game_assist.h"
#include "include/path.h"
#include "include/tchs.h"
#include "include/win.h"

#include <SDL2/SDL_stdinc.h>

#include <stdio.h>
#include <stdlib.h>

extern char currentNotation[CHAR_COUNT_GAME_NOTATION]; // -> game_assist.h
extern int  gameTurn;                                  // -> game.c

SDL_bool stateRunning;

char* pathProg;

int main(int argc, char* argv[]) {

	setGlobalPath(argv[0]);

	printf("Log (main.c): pathProg loaded as %s\n", pathProg);

	if ( winInit() == EXIT_FAILURE ) {

		printf ("Log (main.c): Couldn't initialize the graphical components. Exiting...\n");

		return EXIT_FAILURE;

	}

	stateRunning = SDL_TRUE;
	gameTurn = PIECE_WHITE;

	currentNotation[CHAR_COUNT_GAME_NOTATION - 1] = '\0';

	while (stateRunning) {
		winRender();
		eventHandle();
	}

	winQuit();

	printf("Log (main.c): Cleaning up memory allocations...\n");

	free(pathProg);

	printf("Log (main.c): Goodbye!\n");

	return EXIT_SUCCESS;

}

