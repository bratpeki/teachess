
/*
 * win.c - Handle graphical processes
 *
 * Header: win.h
 */

#include "./include/config.h"
#include "./include/game.h"
#include "./include/game_assist.h"
#include "./include/json.h"
#include "./include/tchs.h"
#include "./include/win.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <json-c/json_object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

SDL_Color     colorText;
SDL_Color     colorTextBoard;

SDL_Rect      rectBoard = { 104, 104, 512, 512 };
SDL_Rect      rectPosX1 = { 104, 624, 32,  32  };
SDL_Rect      rectPosX2 = { 168, 624, 32,  32  };
SDL_Rect      rectPosX3 = { 232, 624, 32,  32  };
SDL_Rect      rectPosX4 = { 296, 624, 32,  32  };
SDL_Rect      rectPosX5 = { 360, 624, 32,  32  };
SDL_Rect      rectPosX6 = { 424, 624, 32,  32  };
SDL_Rect      rectPosX7 = { 488, 624, 32,  32  };
SDL_Rect      rectPosX8 = { 552, 624, 32,  32  };
SDL_Rect      rectPosY1 = { 64,  584, 32,  32  };
SDL_Rect      rectPosY2 = { 64,  520, 32,  32  };
SDL_Rect      rectPosY3 = { 64,  456, 32,  32  };
SDL_Rect      rectPosY4 = { 64,  392, 32,  32  };
SDL_Rect      rectPosY5 = { 64,  328, 32,  32  };
SDL_Rect      rectPosY6 = { 64,  264, 32,  32  };
SDL_Rect      rectPosY7 = { 64,  200, 32,  32  };
SDL_Rect      rectPosY8 = { 64,  136, 32,  32  };
SDL_Rect      rectTitle = { 748, 68,  464, 48  };
SDL_Rect      rectTmp   = { 0,   0,   64,  64  };

SDL_Renderer* rndMain;

SDL_Surface*  surfTitle;
SDL_Surface*  surfTmp;

SDL_Texture*  textAMove;
SDL_Texture*  textBG;
SDL_Texture*  textBoard;
SDL_Texture*  textCheck;
SDL_Texture*  textTitle;
SDL_Texture*  textTmp;

SDL_Texture* textB; SDL_Texture* textb;
SDL_Texture* textK; SDL_Texture* textk;
SDL_Texture* textN; SDL_Texture* textn;
SDL_Texture* textP; SDL_Texture* textp;
SDL_Texture* textQ; SDL_Texture* textq;
SDL_Texture* textR; SDL_Texture* textr;

SDL_Window*   winMain;

SDL_bool boardFlipped = SDL_FALSE;

TTF_Font*     fontMain;

char pathAMove [PATH_TXT_LEN];
char pathB     [PATH_TXT_LEN];
char pathBG    [PATH_TXT_LEN];
char pathBoard [PATH_TXT_LEN];
char pathCheck [PATH_TXT_LEN];
char pathFont  [PATH_TXT_LEN];
char pathK     [PATH_TXT_LEN];
char pathN     [PATH_TXT_LEN];
char pathP     [PATH_TXT_LEN];
char pathQ     [PATH_TXT_LEN];
char pathR     [PATH_TXT_LEN];
char pathb     [PATH_TXT_LEN];
char pathk     [PATH_TXT_LEN];
char pathn     [PATH_TXT_LEN];
char pathp     [PATH_TXT_LEN];
char pathq     [PATH_TXT_LEN];
char pathr     [PATH_TXT_LEN];

char tchsTitleFormat[TITLE_DISP_SIZE + 1]; // title + '\0'

extern char tchsTitle[PATH_TXT_LEN];     // -> tchs.c
extern char tchs[64];                    // -> tchs.c
extern int  tchsTitleLen;                // -> tchs.c
extern int availableMoves[64];           // -> game.c
extern int gameTurn;                     // -> game.c
extern int mouseHold;                    // -> event.c
extern int mouseX, mouseY;               // -> event.c
extern json_object* jsonConfig;          // -> json.c

int boardX, boardY;
int boardXPrev, boardYPrev;
int currPieceType;
int minOffset = 0;
int offset = 0;

char* boardChars[16] = {
	"1", "2", "3", "4", "5", "6", "7", "8",
	"a", "b", "c", "d", "e", "f", "g", "h"
};

// TODO: Remove calcualtion of characters each frame

void boardPosLoad(
	SDL_Surface* surface,
	SDL_Texture* texture,
	SDL_Rect rectangle,
	int boardFlipChar,
	int boardNFlipChar
	) {

	surface = TTF_RenderText_Solid(fontMain, boardChars[boardNFlipChar*(!boardFlipped) + boardFlipChar*(boardFlipped)], colorTextBoard);
	texture = SDL_CreateTextureFromSurface(rndMain, surface);
	SDL_RenderCopy(rndMain, texture, NULL, &rectangle);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

}

void availableMovesLoad() {

	rectTmp.h = 64;
	rectTmp.w = 64;

	for (int i = 0; i < 64; i++) {
		if (availableMoves[i] == 1) {
			rectTmp.x = 104 + 64*(i % 8);
			rectTmp.y = 104 + 64*(int)(i/8);

			SDL_RenderCopy(rndMain, textAMove, NULL, &rectTmp);
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

			if (availableMoves[i*8 + j]) SDL_RenderCopy(rndMain, textAMove, NULL, &rectTmp);
			if (textTmp != NULL)         SDL_RenderCopy(rndMain, textTmp, NULL, &rectTmp);

		}

	}

	return EXIT_SUCCESS;

}

void tchsTitleEdit(int localOffset) {

	if (localOffset < minOffset)                      { offset = minOffset; }
	if (localOffset > PATH_TXT_LEN - TITLE_DISP_SIZE) { offset--; return;   }
	if (localOffset >= tchsTitleLen)                  { offset--; return;   }

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

		if (jsonLoadConf())  return EXIT_FAILURE;
		if (jsonAssetLoad()) return EXIT_FAILURE;

		winMain = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, 0);

		if (winMain != 0) {

			rndMain = SDL_CreateRenderer(winMain, -1, 0);

			textBG    = IMG_LoadTexture(rndMain, pathBG);
			textBoard = IMG_LoadTexture(rndMain, pathBoard);

			textAMove = IMG_LoadTexture(rndMain, pathAMove);
			textCheck = IMG_LoadTexture(rndMain, pathCheck);

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

		} else return EXIT_FAILURE;

	} else return EXIT_FAILURE;

	return EXIT_SUCCESS;

}

void winRender() {

	SDL_RenderClear(rndMain);

	SDL_RenderCopy(rndMain, textBG, NULL, NULL);
	SDL_RenderCopy(rndMain, textBoard, NULL, &rectBoard);
	SDL_RenderCopy(rndMain, textTitle, NULL, &rectTitle);

	tchsTitleEdit(offset);

	surfTitle = TTF_RenderText_Solid(fontMain, tchsTitleFormat, colorText);
	textTitle = SDL_CreateTextureFromSurface(rndMain, surfTitle);

	boardPosLoad(surfTmp, textTmp, rectPosX1, 15, 8 );
	boardPosLoad(surfTmp, textTmp, rectPosX2, 14, 9 );
	boardPosLoad(surfTmp, textTmp, rectPosX3, 13, 10);
	boardPosLoad(surfTmp, textTmp, rectPosX4, 12, 11);
	boardPosLoad(surfTmp, textTmp, rectPosX5, 11, 12);
	boardPosLoad(surfTmp, textTmp, rectPosX6, 10, 13);
	boardPosLoad(surfTmp, textTmp, rectPosX7, 9,  14);
	boardPosLoad(surfTmp, textTmp, rectPosX8, 8,  15);
	boardPosLoad(surfTmp, textTmp, rectPosY1, 7,  0 );
	boardPosLoad(surfTmp, textTmp, rectPosY2, 6,  1 );
	boardPosLoad(surfTmp, textTmp, rectPosY3, 5,  2 );
	boardPosLoad(surfTmp, textTmp, rectPosY4, 4,  3 );
	boardPosLoad(surfTmp, textTmp, rectPosY5, 3,  4 );
	boardPosLoad(surfTmp, textTmp, rectPosY6, 2,  5 );
	boardPosLoad(surfTmp, textTmp, rectPosY7, 1,  6 );
	boardPosLoad(surfTmp, textTmp, rectPosY8, 0,  7 );

	if (mouseHold) {

		// Check if the mouse is in the board space

		if ((mouseX > 104)&&(mouseX < 616)&&(mouseY > 104)&&(mouseY < 616)) {

			/*
			 * Either picking a new piece or moving a piece
			 */

			boardX = (int)((mouseX - 104) / 64); boardX = boardX * (!boardFlipped) + (7 - boardX) * (boardFlipped);
			boardY = (int)((mouseY - 104) / 64); boardY = boardY * (!boardFlipped) + (7 - boardY) * (boardFlipped);

			currPieceType = getPieceType(tchs[getPos64(boardX, boardY)]);

			if (currPieceType == gameTurn) {

				gameGetMoves(boardX, boardY);

				boardXPrev = boardX;
				boardYPrev = boardY;

			}

			if (
				(currPieceType == !gameTurn) ||
				(currPieceType == PIECE_BLANK)
			) {

				if (availableMoves[getPos64(boardX, boardY)] == 1) {

					clearAvailableMoves();

					// Moved piece:
					// printf("%c\n", tchs[getPos64(boardXPrev, boardYPrev)]);

					// Newloc:
					// printf("%c\n", tchs[getPos64(boardX, boardY)]);

					tchs[getPos64(boardX, boardY)] = tchs[getPos64(boardXPrev, boardYPrev)];
					tchs[getPos64(boardXPrev, boardYPrev)] = '-';

					// TODO: Check if a piece is giving a check here

					gameTurn = !gameTurn;

				}

			}

		}

	}

	boardLoad();

	SDL_RenderPresent(rndMain);

}

void winQuit() {

	SDL_DestroyTexture(textBG);
	SDL_DestroyTexture(textBoard);
	SDL_DestroyTexture(textCheck);
	SDL_DestroyTexture(textAMove);
	SDL_DestroyTexture(textTitle);
	SDL_DestroyTexture(textB);
	SDL_DestroyTexture(textK);
	SDL_DestroyTexture(textN);
	SDL_DestroyTexture(textP);
	SDL_DestroyTexture(textQ);
	SDL_DestroyTexture(textR);
	SDL_DestroyTexture(textb);
	SDL_DestroyTexture(textk);
	SDL_DestroyTexture(textn);
	SDL_DestroyTexture(textp);
	SDL_DestroyTexture(textq);
	SDL_DestroyTexture(textr);
	SDL_FreeSurface(surfTitle);

	SDL_DestroyTexture(textTmp);
	SDL_FreeSurface(surfTmp);

	SDL_DestroyWindow(winMain);

	SDL_DestroyRenderer(rndMain);

	TTF_CloseFont(fontMain);
	TTF_Quit();

	IMG_Quit();
	SDL_Quit();

}

