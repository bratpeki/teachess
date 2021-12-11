
/*
 * win.c - Handle window related functionality
 *
 * Header: win.h
 *
 * tchsLoad  -> Load the TCHS array contents onto the screen
 * winInit   -> Initialize the SDL window and necessary components
 * winRender -> Render the visual elements onto the window
 * winQuit   -> Quit the window and clean any memory allocations and calls
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
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
SDL_Rect      rectTmp   = { 0,   0,   64,  64  };

SDL_Renderer* rndMain;

SDL_Texture*  textTmp;

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

extern char tchs[64];           // -> tchs.c

extern json_object* jsonConfig; // -> json.c

extern int mouseX, mouseY;      // -> event.c

int moving = 0;

int tchsLoad() {

	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {

			switch (tchs[i*8 + j]) {

				case 'B': textTmp = textB; break;
				case 'K': textTmp = textK; break;
				case 'N': textTmp = textN; break;
				case 'P': textTmp = textP; break;
				case 'Q': textTmp = textQ; break;
				case 'R': textTmp = textR; break;
				case 'b': textTmp = textb; break;
				case 'k': textTmp = textk; break;
				case 'n': textTmp = textn; break;
				case 'p': textTmp = textp; break;
				case 'q': textTmp = textq; break;
				case 'r': textTmp = textr; break;
				default:  textTmp = NULL;

			}

			if (textTmp != NULL) {

				rectTmp.x = 104 + j*64;
				rectTmp.y = 104 + i*64;

				SDL_RenderCopy(rndMain, textTmp, NULL, &rectTmp);

			}

		}

	}

	return 0;

}

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

	// printf("X: %d\tY: %d\n", mouseX, mouseY);

	if (moving) {



	}
	else tchsLoad();

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

