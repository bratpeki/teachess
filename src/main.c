
/*
 * main.c - The main C execution source file
 */

#include <stdio.h>
#include <stdlib.h>

#include "./include/event.h"
#include "./include/path.h"
#include "./include/win.h"
#include "./include/tchs.h"

char *pathProg;
int   stateRunning;

extern int gameTurn; // -> game.c

int main(int argc, char* argv[]) {

	setGlobalPath(argv[0]);

	printf("Log (main.c): pathProg loaded as %s\n", pathProg);

	if ( !winInit() ) stateRunning = 1;
	else              return 1;

	// tchsRead("b-ruy-lopez-mainline-5-moves");

	while (stateRunning) {
		eventHandle();
		winRender();
	}

	winQuit();

	printf("Log (main.c): Cleaning up memory allocations...\n");

	free(pathProg);

	printf("Log (main.c): Goodbye!\n");

	return 0;

}

