
/*
 * game_assist.c - Handle game-related assisting functions
 *
 * Header: game_assist.h
 */

#include "include/game.h"
#include "include/game_assist.h"

#include <SDL2/SDL_stdinc.h>

extern char charTmp;            // -> tmp.c
extern char tchs[64];           // -> tchs.c
extern int  availableMoves[64]; // -> game.c
extern int  spotX;              // -> game.c
extern int  spotY;              // -> game.c

char boardOuterChars[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
char currentNotation[CHAR_COUNT_GAME_NOTATION];
int  bishopTmp;

int getPieceType(char c) {

	if ( (c == 'B') ||
		 (c == 'C') ||
		 (c == 'E') ||
		 (c == 'J') ||
		 (c == 'K') ||
		 (c == 'L') ||
		 (c == 'N') ||
		 (c == 'P') ||
		 (c == 'Q') ||
		 (c == 'R') )
		return PIECE_WHITE;

	else if ( (c == '.') ||
			  (c == '-') )
		return PIECE_BLANK;

	else
		return PIECE_BLACK;

};

void getGameNotation(int x1, int y1, int x2, int y2) {

	/* Clearing the content of the game notation */

	for (int i = 0; i < CHAR_COUNT_GAME_NOTATION - 1; i++) currentNotation[i] = ' ';

	// printf ("1. %d-%d\n2. %d-%d\n", x1, y1, x2, y2);
	printf("%c%d\n", boardOuterChars[x2], 8 - y2);

}

int checkSpotType(int pieceX, int pieceY, int pieceType) {

	// TODO: return "out of bounds" exit code rather than false

	if ((pieceX < 0) || (pieceX > 7) || (pieceY < 0) || (pieceY > 7)) return SDL_FALSE;

	return (getPieceType(tchs[getPos64(pieceX, pieceY)]) == pieceType);

}

void clearAvailableMoves() { for (unsigned int i = 0; i < 64; i++) availableMoves[i] = 0; }

// TODO: Check if boardX and boardY are needed here
//       Maybe a check system needs them there

SDL_bool gameCheckLine(
		int boardX, int boardY,
		int coef1, int coef2,
		int pieceCollType,
		int* arrayToFill
		) {

	bishopTmp = 0;

	while (++bishopTmp) {

		spotX = boardX + coef1 * bishopTmp;
		spotY = boardY + coef2 * bishopTmp;

		if (checkSpotType(spotX, spotY, pieceCollType)) {

			arrayToFill[getPos64(spotX, spotY)] = 1;

			// TODO: Check if the collision with the king is achieved

			charTmp = tchs[getPos64(spotX, spotY)];

			break;

		}
		else if (checkSpotType(spotX, spotY, PIECE_BLANK))
			arrayToFill[getPos64(spotX, spotY)] = 1;
		else break;

	}

	return SDL_FALSE;

}

