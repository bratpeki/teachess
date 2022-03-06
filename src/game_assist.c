
/*
 * game_assist.c - Handle game-related assisting functions
 *
 * Header: game_assist.h
 */

#include <SDL2/SDL_stdinc.h>

#include "./include/game.h"
#include "./include/game_assist.h"

extern char tchs[64];           // -> tchs.c
extern int  availableMoves[64]; // -> game.c
extern int  spotX;              // -> game.c
extern int  spotY;              // -> game.c
extern char charTmp;            // -> tmp.c

int bishopTmp;

int getPieceType(char c) {

	if ( (c == 'B') ||
		 (c == 'P') ||
		 (c == 'C') ||
		 (c == 'E') ||
		 (c == 'K') ||
		 (c == 'N') ||
		 (c == 'R') ||
		 (c == 'X') ||
		 (c == 'Y') ||
		 (c == 'Q') )
		return PIECE_WHITE;

	else if ( (c == '.') ||
			  (c == '-') )
		return PIECE_BLANK;

	else
		return PIECE_BLACK;

};

int checkSpotType(int pieceX, int pieceY, int pieceType) {

	if ((pieceX < 0) || (pieceX > 7) || (pieceY < 0) || (pieceY > 7)) return SDL_FALSE;

	return (getPieceType(tchs[getPos64(pieceX, pieceY)]) == pieceType);

}

void clearAvailableMoves() { for (unsigned int i = 0; i < 64; i++) availableMoves[i] = 0; }

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

			break;
		}
		else if (checkSpotType(spotX, spotY, PIECE_BLANK)) {
			arrayToFill[getPos64(spotX, spotY)] = 1;
		}
		else break;

	}

	return SDL_FALSE;

}

