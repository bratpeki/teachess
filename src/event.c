
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
#include "./include/tchs.h"

SDL_Event event;

int mouseHold = 0;
int mouseX, mouseY = 0;

extern int stateRunning; // -> main.c
extern int boardFlipped; // -> win.c

void eventHandle() {

	while (SDL_PollEvent(&event)) {

		SDL_GetMouseState(&mouseX, &mouseY);

		switch (event.type) {

			case SDL_QUIT:
				stateRunning = 0;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseHold = 1;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseHold = 0;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

					case SDLK_ESCAPE:
						stateRunning = 0;
						break;

					case SDLK_f:
						boardFlipped = !boardFlipped;
						break;

					case SDLK_1:
						tchsRead("w-default");
						break;

					case SDLK_2:
						tchsRead("b-ruy-lopez-mainline-5-moves");
						break;

				}

		}

	}

}

