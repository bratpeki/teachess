
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

SDL_Texture*  textBG;
SDL_Texture*  textBoard;

SDL_Texture*  textB;
SDL_Texture*  textK;
SDL_Texture*  textN;
SDL_Texture*  textP;
SDL_Texture*  textQ;
SDL_Texture*  textR;

SDL_Window*   winMain;

char          pathBG   [64];
char          pathBoard[64];

extern json_object* jsonConfig;

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		IMG_Init(IMG_INIT_PNG);

		// Check if the JSON file can be loaded successfully

		if (!jsonLoad(PATH_JSON_CONFIG)) {
			dp("PATH_JSON_CONFIG loaded successfully.\n");
		}
		else {
			dp("PATH_JSON_CONFIG couldn't be loaded.\n");
			return 1;
		}

		// Check and asign the JSON object values where they belong
		// TODO:
		//     check that namestring aren't too large
		//     check that files exist

		json_object_object_foreach(jsonConfig, key, val) {

			if ( !strcmp(key, "boardImage")) {
				sprintf(pathBoard, "./img/board/%s.png", json_object_get_string(val));
				if ( access(pathBoard, F_OK) == 0 ) {
					dp("Board image loaded successfully.\n");
				}
				else {
					dp("! Board image loaded unsuccessfully.\n");
					return 1;
				}
			}

			if ( !strcmp(key, "bgImage")) {
				sprintf(pathBG, "./img/background/%s.png", json_object_get_string(val));
			}
		}

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

