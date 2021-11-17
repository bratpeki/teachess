
/*
 * win.c - Handle window related functionality
 *
 * Header: win.h
 *
 * winInit   -> Initialize the SDL window and necessary components
 * winRender -> Render the visual elements onto the window
 * winQuit   -> Quit the window and clean any memory allocations and calls
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include "./include/win.h"

SDL_Window*   winMain = NULL;
SDL_Renderer* renMain = NULL;

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);

		if (winMain != 0) {

			renMain = SDL_CreateRenderer(winMain, -1, 0);

		}

	} else return 0;

	return 1;

}

void winRender() {

	SDL_SetRenderDrawColor(renMain, 0x4a, 0x4a, 0x4a, 0xFF);
	SDL_RenderClear(renMain);

	SDL_RenderPresent(renMain);

}

void winQuit() {

	SDL_Quit();

}

