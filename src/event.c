
/*
 * event.c - Handle keyboard events
 *
 * Header: event.h
 *
 * eventHandle -> Go through key inputs and respond appropriately
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

#include "./include/event.h"

SDL_Event event;

int mouseX, mouseY;

extern int stateRunning; // -> main.c
extern int moving;       // -> win.c

void eventHandle() {

	while (SDL_PollEvent(&event)) {

		SDL_GetMouseState(&mouseX, &mouseY);

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

			case SDL_MOUSEBUTTONDOWN:
				moving = 1;
				break;

			case SDL_MOUSEBUTTONUP:
				moving = 0;
				break;

		}

	}

}

