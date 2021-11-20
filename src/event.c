
/*
 * event.c - Handle keyboard events
 *
 * Header: event.h
 *
 * eventHandle -> Go through key inputs and respond appropriately
 */

#include <SDL2/SDL.h>

#include "./include/event.h"

SDL_Event event;

extern int stateRunning; // -> main.c

void eventHandle() {

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

			case SDL_QUIT:
				stateRunning = 0;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

					case SDLK_ESCAPE:
						stateRunning = 0;
						break;

				}

		}

	}

}

