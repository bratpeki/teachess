
/*
 * main.c - The main C execution source file
 */

#include "./include/event.h"
#include "./include/win.h"

#include <string.h>
#include <stdio.h>

extern int stateRunning;

// TODO: Replace './' paths with the absolute path

int main(int argc, char* argv[]) {

	if ( !winInit() ) stateRunning = 1;
	else              return 1;

	while (stateRunning) {
		eventHandle();
		winRender();
	}

	winQuit();

	return 0;

}

