
#ifndef H_TEACHESS_GAME_ASSIST
#define H_TEACHESS_GAME_ASSIST

#include <SDL2/SDL_stdinc.h>

/*
 * By some, the maximum number of characters for a move is 8
 * more is included for padding and the "\0" character
 */

#define CHAR_COUNT_GAME_NOTATION 10

/* Return the piece type */

int getPieceType(char c);

/* Check that the spot on (spotX, spotY) is of pieceType */

int checkSpotType(int pieceX, int pieceY, int pieceType);

/* Clear availableMoves */

void clearAvailableMoves();

/*
 * Convert piece movement for (x1, y1) to (x2, y2) into proper game notatio
 * Store the notation in currentNotation
 */

void getGameNotation(int x1, int y1, int x2, int y2);

/*
 * Check one diagonal of a bishop's, rook's or queen's movement
 * coef1 and coef2 should be either 1 or -1
 * The retrun value is weather the bishop's path ran into an opposite king
 */

SDL_bool gameCheckLine(int boardX, int boardY, int coef1, int coef2, int pieceCollType, int* arrayToFill);

#endif

