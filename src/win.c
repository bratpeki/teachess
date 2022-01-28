
/*
 * win.c - Handle window related functionality
 *
 * Header: win.h
 *
 * tchsLoad      -> Load the TCHS array contents onto the screen
 * tchsTitleEdit -> Format the TCHS title into TITLE_DISP_SIZE characters which are displayed
 * winInit       -> Initialize the SDL window and necessary components
 * winRender     -> Render the visual elements onto the window
 * winQuit       -> Quit the window and clean any memory allocations and calls
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

// FONTWORK
SDL_Color colorFont = { 255, 255, 255 };
SDL_Surface *surfFont;
SDL_Texture *textFont;
TTF_Font *fontMain;
SDL_Rect rectFont = { 740, 60, 480, 64 };

char          pathBG    [PATH_TXT_LEN];
char          pathBoard [PATH_TXT_LEN];
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
extern int mouseHold;                    // -> event.c
extern int mouseX, mouseY;               // -> event.c
extern json_object* jsonConfig;          // -> json.c

int boardFlipped = 0;
int mouseInBoard = 0;

int boardX, boardY;
int offset = 0;

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

				rectTmp.x = 104 + (j*64)*(!boardFlipped) + ((7-j)*64)*(boardFlipped);
				rectTmp.y = 104 + (i*64)*(!boardFlipped) + ((7-i)*64)*(boardFlipped);

				SDL_RenderCopy(rndMain, textTmp, NULL, &rectTmp);

			}

		}

	}

	return 0;

}

// TODO: Work on the system that stop you from overdoing the offsetting

void tchsTitleEdit(int localOffset) {

	// Making sure the offset is proper
	if (localOffset < 0) offset = 0;
	if (localOffset > PATH_TXT_LEN - TITLE_DISP_SIZE) { offset--; return; }

	// Clearing tchsTitleFormat
	for (int i = 0; i < TITLE_DISP_SIZE; i++) tchsTitleFormat[i] = ' ';

	// Formatting
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

			// FONTWORK
			tchsTitleFormat[TITLE_DISP_SIZE] = '\0'; // this can be defined just once
			fontMain = TTF_OpenFont(pathFont, 24);
			surfFont = TTF_RenderText_Solid(fontMain, tchsTitleFormat, colorFont);
			textFont = SDL_CreateTextureFromSurface(rndMain, surfFont);

		}

	} else return 1;

	return 0;

}

void winRender() {

	SDL_RenderClear(rndMain);

	SDL_RenderCopy(rndMain, textBG, NULL, NULL);
	SDL_RenderCopy(rndMain, textBoard, NULL, &rectBoard);

	// FONTWORK
	SDL_RenderCopy(rndMain, textFont, NULL, &rectFont);
	tchsTitleEdit(offset);
	surfFont = TTF_RenderText_Solid(fontMain, tchsTitleFormat, colorFont);
	textFont = SDL_CreateTextureFromSurface(rndMain, surfFont);

	if (mouseHold) {

		mouseInBoard = ((mouseX > 104)&&(mouseX < 616)&&(mouseY > 104)&&(mouseY < 616));

		if (mouseInBoard) {

			boardX = (int)((mouseX-104)/64);
			boardY = (int)((mouseY-104)/64);
			printf("%c\n", tchsGetPiece(boardX, boardY, boardFlipped));

		}

	}
	else tchsLoad();

	SDL_RenderPresent(rndMain);

}

void winQuit() {

	// FONTWORK
	SDL_FreeSurface(surfFont);
	SDL_DestroyTexture(textFont);

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

	// FONTWORK
	TTF_CloseFont(fontMain);
	TTF_Quit();

	IMG_Quit();
	SDL_Quit();

}

