
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
#include "./include/win.h"

SDL_Rect      rectBoard = { 104, 104, 512, 512 };
SDL_Rect      rectPawn  = { 104, 488, 64, 64 };

SDL_Renderer* rndMain;

SDL_Texture*  textBG;
SDL_Texture*  textBoard;

SDL_Texture*  textB;
SDL_Texture*  textK;
SDL_Texture*  textN;
SDL_Texture*  textP;
SDL_Texture*  textQ;
SDL_Texture*  textR;
SDL_Texture*  textb;
SDL_Texture*  textk;
SDL_Texture*  textn;
SDL_Texture*  textp;
SDL_Texture*  textq;
SDL_Texture*  textr;

SDL_Window*   winMain;

char          pathBG    [PATH_TEXT_LENGHT];
char          pathBoard [PATH_TEXT_LENGHT];
char          pathPiece [PATH_TEXT_LENGHT];

char          pathB     [PATH_TEXT_LENGHT];
char          pathK     [PATH_TEXT_LENGHT];
char          pathN     [PATH_TEXT_LENGHT];
char          pathP     [PATH_TEXT_LENGHT];
char          pathQ     [PATH_TEXT_LENGHT];
char          pathR     [PATH_TEXT_LENGHT];
char          pathb     [PATH_TEXT_LENGHT];
char          pathk     [PATH_TEXT_LENGHT];
char          pathn     [PATH_TEXT_LENGHT];
char          pathp     [PATH_TEXT_LENGHT];
char          pathq     [PATH_TEXT_LENGHT];
char          pathr     [PATH_TEXT_LENGHT];

extern json_object* jsonConfig; // -> json.c

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		IMG_Init(IMG_INIT_PNG);

		if (jsonLoadConf()) return 1;
		if (jsonTextLoad()) return 1;

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, 0);

		if (winMain != 0) {

			rndMain = SDL_CreateRenderer(winMain, -1, 0);

			textBG    = IMG_LoadTexture(rndMain, pathBG);
			textBoard = IMG_LoadTexture(rndMain, pathBoard);
			textP     = IMG_LoadTexture(rndMain, pathP);

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

	SDL_DestroyRenderer(rndMain);

	SDL_DestroyTexture(textBG);
	SDL_DestroyTexture(textBoard);

	SDL_DestroyTexture(textB);
	SDL_DestroyTexture(textb);
	SDL_DestroyTexture(textK);
	SDL_DestroyTexture(textk);
	SDL_DestroyTexture(textN);
	SDL_DestroyTexture(textn);
	SDL_DestroyTexture(textP);
	SDL_DestroyTexture(textp);
	SDL_DestroyTexture(textQ);
	SDL_DestroyTexture(textq);
	SDL_DestroyTexture(textR);
	SDL_DestroyTexture(textr);

	SDL_DestroyWindow(winMain);

	IMG_Quit();
	SDL_Quit();

}

