
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

#include <json-c/json.h>
#include <json-c/json_object.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./include/config.h"
#include "./include/json.h"
#include "./include/log.h"
#include "./include/win.h"

SDL_Rect      rectBoard = { 104, 104, 512, 512 };
SDL_Rect      rectPawn  = { 104, 488, 64, 64 };
SDL_Renderer* rndMain;

SDL_Window*   winMain;

char          pathBG   [64];
char          pathBoard[64];

extern SDL_Texture*  textBG;
extern SDL_Texture*  textBoard;

extern SDL_Texture*  textB;
extern SDL_Texture*  textK;
extern SDL_Texture*  textN;
extern SDL_Texture*  textP;
extern SDL_Texture*  textQ;
extern SDL_Texture*  textR;

extern json_object* jsonConfig;

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		IMG_Init(IMG_INIT_PNG);

		if (jsonLoad(PATH_JSON_CONFIG))      return 1;
		if (jsonTextLoad(pathBG, pathBoard)) return 1;

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, 0);

		if (winMain != 0) {

			rndMain = SDL_CreateRenderer(winMain, -1, 0);

			// Asign the textures

			textBG    = IMG_LoadTexture(rndMain, pathBG);
			textBoard = IMG_LoadTexture(rndMain, pathBoard);
			textP     = IMG_LoadTexture(rndMain, "./img/piece/default/P.png");

		}

	} else return 1;

	return 0;

}

void winRender() {

	SDL_RenderClear(rndMain);

	SDL_RenderCopy(rndMain, textBG, NULL, NULL);
	SDL_RenderCopy(rndMain, textBoard, NULL, &rectBoard);
	SDL_RenderCopy(rndMain, textP, NULL, &rectPawn);

	SDL_RenderPresent(rndMain);

}

void winQuit() {

	SDL_DestroyTexture(textP);

	SDL_DestroyRenderer(rndMain);
	SDL_DestroyTexture(textBG);
	SDL_DestroyTexture(textBoard);
	SDL_DestroyWindow(winMain);

	IMG_Quit();
	SDL_Quit();

}

