
/*
 * main.c - The main C execution source file
 */

#include "./include/win.h"
#include "./include/event.h"

extern int stateRunning;

int main(int argc, char* argv[]) {

	if ( winInit() ) stateRunning = 1;
	else             return 1;

	while (stateRunning) {
		eventHandle();
		winRender();
	}

	winQuit();

	return 0;

}

