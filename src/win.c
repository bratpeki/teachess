
/*
 * win.c - Handle window related functionality
 *
 * Header: win.h
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <json-c/json.h>
#include <json-c/json_object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./include/config.h"
#include "./include/game.h"
#include "./include/json.h"
#include "./include/tchs.h"
#include "./include/win.h"

// https://stackoverflow.com/a/40493179/10857616

SDL_Color     colorFont = { 153, 153, 153, 255 };

SDL_Rect      rectBoard = { 104, 104, 512, 512 };
SDL_Rect      rectTitle = { 748, 68,  464, 48  };
SDL_Rect      rectTmp   = { 0,   0,   64,  64  };

SDL_Renderer* rndMain;

SDL_Surface*  surfTitle;

TTF_Font*     fontMain;

SDL_Texture*  textTitle;
SDL_Texture*  textTmp;
SDL_Texture*  textBG;
SDL_Texture*  textBoard;
SDL_Texture*  textMove;
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

char          pathBG    [PATH_TXT_LEN];
char          pathBoard [PATH_TXT_LEN];
char          pathAMove [PATH_TXT_LEN];
char          pathB     [PATH_TXT_LEN];
char          pathK     [PATH_TXT_LEN];
char          pathN     [PATH_TXT_LEN];
char          pathP     [PATH_TXT_LEN];
char          pathQ     [PATH_TXT_LEN];
char          pathR     [PATH_TXT_LEN];
char          pathb     [PATH_TXT_LEN];
char          pathk     [PATH_TXT_LEN];
char          pathn     [PATH_TXT_LEN];
char          pathp     [PATH_TXT_LEN];
char          pathq     [PATH_TXT_LEN];
char          pathr     [PATH_TXT_LEN];
char          pathFont  [PATH_TXT_LEN];

// The "+1" is there to include the null escape character
char tchsTitleFormat[TITLE_DISP_SIZE + 1];

extern char tchsTitle[PATH_TXT_LEN];     // -> tchs.c
extern char tchs[64];                    // -> tchs.c
extern int tchsTitleLen;                 // -> tchs.c
extern int availableMoves[64];           // -> game.c
extern int mouseHold;                    // -> event.c
extern int mouseX, mouseY;               // -> event.c
extern json_object* jsonConfig;          // -> json.c

int boardFlipped = 0;

int offset = 0;
int minOffset = 0;

void availableMovesLoad() {

	rectTmp.h = 64;
	rectTmp.w = 64;

	for (int i = 0; i < 64; i++) {
		if (availableMoves[i] == 1) {
			rectTmp.x = 104 + 64*(i % 8);
			rectTmp.y = 104 + 64*(int)(i/8);

			SDL_RenderCopy(rndMain, textMove, NULL, &rectTmp);
		}
	}

}

int boardLoad() {

	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {

			switch (tchs[i*8 + j]) {

				case 'B': textTmp = textB; break;
				case 'C': textTmp = textK; break;
				case 'E': textTmp = textP; break;
				case 'K': textTmp = textK; break;
				case 'N': textTmp = textN; break;
				case 'P': textTmp = textP; break;
				case 'Q': textTmp = textQ; break;
				case 'R': textTmp = textR; break;
				case 'b': textTmp = textb; break;
				case 'c': textTmp = textk; break;
				case 'e': textTmp = textp; break;
				case 'k': textTmp = textk; break;
				case 'n': textTmp = textn; break;
				case 'p': textTmp = textp; break;
				case 'q': textTmp = textq; break;
				case 'r': textTmp = textr; break;
				default:  textTmp = NULL;

			}

			rectTmp.x = 104 + (j*64)*(!boardFlipped) + ((7-j)*64)*(boardFlipped);
			rectTmp.y = 104 + (i*64)*(!boardFlipped) + ((7-i)*64)*(boardFlipped);

			if (availableMoves[i*8 + j])
				SDL_RenderCopy(rndMain, textMove, NULL, &rectTmp);

			if (textTmp != NULL)
				SDL_RenderCopy(rndMain, textTmp, NULL, &rectTmp);


		}

	}

	return 0;

}

// TODO: Work on the system that stop you from overdoing the offsetting

void tchsTitleEdit(int localOffset) {

	if (localOffset < minOffset) offset = minOffset;
	if (localOffset > PATH_TXT_LEN - TITLE_DISP_SIZE) { offset--; return; }

	for (int i = 0; i < TITLE_DISP_SIZE; i++) tchsTitleFormat[i] = ' ';

	for (int i = 0; i < TITLE_DISP_SIZE; i++) {

		if (tchsTitle[offset + i] == '\0') break;
		else tchsTitleFormat[i] = tchsTitle[offset + i];

	}

}

int winInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		IMG_Init(IMG_INIT_PNG);
		TTF_Init();

		if (jsonLoadConf()) return 1;
		if (jsonTextLoad()) return 1;

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, 0);

		if (winMain != 0) {

			rndMain = SDL_CreateRenderer(winMain, -1, 0);

			textBG    = IMG_LoadTexture(rndMain, pathBG);
			textBoard = IMG_LoadTexture(rndMain, pathBoard);

			textMove  = IMG_LoadTexture(rndMain, pathAMove);

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

			tchsTitleFormat[TITLE_DISP_SIZE] = '\0';

			fontMain = TTF_OpenFont(pathFont, 24);

		}

	} else return 1;

	return 0;

}

void winRender() {

	SDL_RenderClear(rndMain);

	SDL_RenderCopy(rndMain, textBG, NULL, NULL);
	SDL_RenderCopy(rndMain, textBoard, NULL, &rectBoard);
	SDL_RenderCopy(rndMain, textTitle, NULL, &rectTitle);

	tchsTitleEdit(offset);

	surfTitle = TTF_RenderText_Solid(fontMain, tchsTitleFormat, colorFont);
	textTitle = SDL_CreateTextureFromSurface(rndMain, surfTitle);

	if (mouseHold) {

		// Check if the mouse is in the board space

		if ((mouseX > 104)&&(mouseX < 616)&&(mouseY > 104)&&(mouseY < 616)) {

			/*
			 * Either picking a new piece or moving a piece
			 */

			gameGetMoves((int)((mouseX-104)/64), (int)((mouseY-104)/64));

		}

	}
	boardLoad();

	SDL_RenderPresent(rndMain);

}

void winQuit() {

	SDL_FreeSurface(surfTitle);
	SDL_DestroyTexture(textTitle);

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

	TTF_CloseFont(fontMain);
	TTF_Quit();

	IMG_Quit();
	SDL_Quit();

}

