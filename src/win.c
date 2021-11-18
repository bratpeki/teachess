
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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include <stdio.h>
#include <string.h>

#include "./include/win.h"
#include "./include/config.h"

SDL_Rect      rectBoard = { 104, 104, 512, 512 };
SDL_Rect      rectPawn  = { 104, 488, 64, 64 };

SDL_Renderer* renMain;

SDL_Texture*  textBG;
SDL_Texture*  textBoard;
SDL_Texture*  textPawn;

SDL_Window*   winMain;

char          pathBG[128];
char          pathBoard[128];

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, 0);

		if (winMain != 0) {

			IMG_Init(IMG_INIT_PNG);

			renMain = SDL_CreateRenderer(winMain, -1, 0);

			sprintf(pathBoard, "./img/board/%s.png", IMG_BOARD);
			sprintf(pathBG, "./img/background/%s.png", IMG_BG);

			textBG    = IMG_LoadTexture(renMain, pathBG);
			textBoard = IMG_LoadTexture(renMain, pathBoard);
			textPawn  = IMG_LoadTexture(renMain, "./img/piece/default/P.png");

		}

	} else return 0;

	return 1;

}

void winRender() {

	SDL_RenderClear(renMain);

	SDL_RenderCopy(renMain, textBG, NULL, NULL);
	SDL_RenderCopy(renMain, textBoard, NULL, &rectBoard);
	SDL_RenderCopy(renMain, textPawn, NULL, &rectPawn);

	SDL_RenderPresent(renMain);

}

void winQuit() {

	SDL_DestroyTexture(textPawn);

	SDL_DestroyRenderer(renMain);
	SDL_DestroyTexture(textBG);
	SDL_DestroyTexture(textBoard);
	SDL_DestroyWindow(winMain);

	IMG_Quit();
	SDL_Quit();

}

