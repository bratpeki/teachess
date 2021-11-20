
/*
 * main.c - The main C execution source file
 */

#include "./include/event.h"
#include "./include/path.h"
#include "./include/win.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pathProg;
int   stateRunning;

int main(int argc, char* argv[]) {

	setGlobalPath(argv[0]);

	printf("Log: pathProg loaded as %s\n", pathProg);

	if ( !winInit() ) stateRunning = 1;
	else              return 1;

	while (stateRunning) {
		eventHandle();
		winRender();
	}

	winQuit();

	printf("Log: Cleaning up memory allocations...\n");

	free(pathProg);

	printf("Log: Goodbye!\n");

	return 0;

}

