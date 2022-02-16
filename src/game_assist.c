
/*
 * game_assist.c - Handle game-related assisting functions
 *
 * Header: game_assist.h
 */

#include "./include/game.h"
#include "./include/game_assist.h"

extern char tchs[64];           // -> tchs.c
extern int  availableMoves[64]; // -> game.c

int getPieceType(char c) {

	if ( (c == 'P') ||
		 (c == 'E') ||
		 (c == 'B') ||
		 (c == 'N') ||
		 (c == 'R') ||
		 (c == 'K') ||
		 (c == 'Q') )
		return PIECE_WHITE;

	else if ( (c == '.') ||
			  (c == '-') )
		return PIECE_BLANK;

	else
		return PIECE_BLACK;

};

int checkSpotType(int pieceX, int pieceY, int pieceType) {

	if ((pieceX < 0) || (pieceX > 7) || (pieceY < 0) || (pieceY > 7)) return 0;

	return (getPieceType(tchs[getPos64(pieceX, pieceY)]) == pieceType);

}

void clearAvailableMoves() { for (unsigned int i = 0; i < 64; i++) availableMoves[i] = 0; }

