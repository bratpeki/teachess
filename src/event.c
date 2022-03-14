
/*
 * event.c - Handle keyboard events
 *
 * Header: event.h
 */

#include "./include/event.h"
#include "./include/tchs.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>

SDL_Event event;

int mouseHold = 0;
int mouseX, mouseY = 0;

// TODO: stateRunning and boardFlipped should be SDL_bool

extern int stateRunning; // -> main.c
extern int boardFlipped; // -> win.c
extern int offset;       // -> win.c
extern int minOffset;    // -> win.c

void eventHandle() {

	// TODO: Do I need "!= SDL_FALSE"

	if (SDL_WaitEvent(&event) != SDL_FALSE) {

		SDL_GetMouseState(&mouseX, &mouseY);

		switch (event.type) {

			case SDL_QUIT:            stateRunning = SDL_FALSE; break;
			case SDL_MOUSEBUTTONDOWN: mouseHold    = SDL_TRUE;  break;
			case SDL_MOUSEBUTTONUP:   mouseHold    = SDL_FALSE; break;

			case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {

				// Exiting
				case SDLK_ESCAPE: stateRunning = SDL_FALSE; break;

				// TODO: Handle the board characters only when flipping the board
				//       This spares the CPU of having to calculate what character is needed every render

				// Flip the board
				case SDLK_f: boardFlipped = !boardFlipped; break;

				// Offsetting
				case SDLK_a: offset--;           break;
				case SDLK_d: offset++;           break;
				case SDLK_s: offset = minOffset; break;

				case SDLK_1:
					tchsRead("wDefault");
					break;

				case SDLK_2:
					tchsRead("bRuy Lopez Mainline (5 Moves)");
					break;

				case SDLK_3:
					tchsRead("wRook Endgame Example");
					break;

				case SDLK_4:
					tchsRead("wExample");
					break;

			}

		}

	}

}

