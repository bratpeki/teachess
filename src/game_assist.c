
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
extern int  intTmp;             // -> tmp.c
extern int  spotX;              // -> game.c
extern int  spotY;              // -> game.c

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

}

int checkSpotType(int pieceX, int pieceY, int pieceType) {

	if ((pieceX < 0) || (pieceX > 7) || (pieceY < 0) || (pieceY > 7)) return STATE_OUT_OF_BOUNDS;

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

	intTmp = 0;

	while (++intTmp) {

		spotX = boardX + coef1 * intTmp;
		spotY = boardY + coef2 * intTmp;

		if (checkSpotType(spotX, spotY, pieceCollType) == SDL_TRUE) {

			arrayToFill[getPos64(spotX, spotY)] = 1;

			// TODO: Check if the collision with the king is achieved

			charTmp = tchs[getPos64(spotX, spotY)];

			break;

		}
		else if (checkSpotType(spotX, spotY, PIECE_BLANK) == SDL_TRUE)
			arrayToFill[getPos64(spotX, spotY)] = 1;
		else break;

	}

	return SDL_FALSE;

}

