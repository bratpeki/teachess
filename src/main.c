
/*
 * main.c - The main C execution source file
 */

#include "./include/event.h"
#include "./include/game.h"
#include "./include/path.h"
#include "./include/tchs.h"
#include "./include/win.h"

#include <SDL2/SDL_stdinc.h>

#include <stdio.h>
#include <stdlib.h>

extern int gameTurn; // -> game.c

SDL_bool stateRunning;

char* pathProg;

int main(int argc, char* argv[]) {

	setGlobalPath(argv[0]);

	printf("Log (main.c): pathProg loaded as %s\n", pathProg);

	if ( winInit() ) {

		printf ("Log (main.c): Couldn't initialize the graphical components. Exiting...\n");

		return EXIT_FAILURE;

	}

	else {

		stateRunning = SDL_TRUE;
		gameTurn = PIECE_WHITE;

		winRender();

		while (stateRunning) {
			eventHandle();
		}

		winQuit();

		printf("Log (main.c): Cleaning up memory allocations...\n");

		free(pathProg);

		printf("Log (main.c): Goodbye!\n");

		return EXIT_SUCCESS;

	}

}

