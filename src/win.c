
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
#include "./include/tchs.h"
#include "./include/win.h"

SDL_Rect      rectBoard = { 104, 104, 512, 512 };

SDL_Rect      rectP1 = { 104, 488, 64, 64 };
SDL_Rect      rectP2 = { 168, 488, 64, 64 };
SDL_Rect      rectP3 = { 232, 488, 64, 64 };
SDL_Rect      rectP4 = { 296, 488, 64, 64 };
SDL_Rect      rectP5 = { 360, 488, 64, 64 };
SDL_Rect      rectP6 = { 424, 488, 64, 64 };
SDL_Rect      rectP7 = { 488, 488, 64, 64 };
SDL_Rect      rectP8 = { 552, 488, 64, 64 };

SDL_Rect      rectR1 = { 104, 552, 64, 64 };
SDL_Rect      rectN1 = { 168, 552, 64, 64 };
SDL_Rect      rectB1 = { 232, 552, 64, 64 };
SDL_Rect      rectK  = { 296, 552, 64, 64 };
SDL_Rect      rectQ  = { 360, 552, 64, 64 };
SDL_Rect      rectB2 = { 424, 552, 64, 64 };
SDL_Rect      rectN2 = { 488, 552, 64, 64 };
SDL_Rect      rectR2 = { 552, 552, 64, 64 };

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

		tchsRead("default");

		if (winMain != 0) {

			rndMain = SDL_CreateRenderer(winMain, -1, 0);

			textBG    = IMG_LoadTexture(rndMain, pathBG);
			textBoard = IMG_LoadTexture(rndMain, pathBoard);

			textB     = IMG_LoadTexture(rndMain, pathB);
			textK     = IMG_LoadTexture(rndMain, pathK);
			textN     = IMG_LoadTexture(rndMain, pathN);
			textP     = IMG_LoadTexture(rndMain, pathP);
			textQ     = IMG_LoadTexture(rndMain, pathQ);
			textR     = IMG_LoadTexture(rndMain, pathR);
			textb     = IMG_LoadTexture(rndMain, pathb);
			textk     = IMG_LoadTexture(rndMain, pathk);
			textn     = IMG_LoadTexture(rndMain, pathn);
			textp     = IMG_LoadTexture(rndMain, pathp);
			textq     = IMG_LoadTexture(rndMain, pathq);
			textr     = IMG_LoadTexture(rndMain, pathr);

		}

	} else return 1;

	return 0;

}

void winRender() {

	SDL_RenderClear(rndMain);

	SDL_RenderCopy(rndMain, textBG, NULL, NULL);
	SDL_RenderCopy(rndMain, textBoard, NULL, &rectBoard);

	SDL_RenderCopy(rndMain, textP, NULL, &rectP1);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP2);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP3);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP4);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP5);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP6);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP7);
	SDL_RenderCopy(rndMain, textP, NULL, &rectP8);

	SDL_RenderCopy(rndMain, textR, NULL, &rectR1);
	SDL_RenderCopy(rndMain, textN, NULL, &rectN1);
	SDL_RenderCopy(rndMain, textB, NULL, &rectB1);
	SDL_RenderCopy(rndMain, textK, NULL, &rectK);
	SDL_RenderCopy(rndMain, textQ, NULL, &rectQ);
	SDL_RenderCopy(rndMain, textB, NULL, &rectB2);
	SDL_RenderCopy(rndMain, textN, NULL, &rectN2);
	SDL_RenderCopy(rndMain, textR, NULL, &rectR2);

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

