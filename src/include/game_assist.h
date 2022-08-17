
#ifndef H_TEACHESS_GAME_ASSIST
#define H_TEACHESS_GAME_ASSIST

#include <SDL2/SDL_stdinc.h>

/*
 * By some, the maximum number of characters for a move is 8
 * more is included for padding and the "\0" character
 */

#define CHAR_COUNT_GAME_NOTATION 10

/*
 * Piece type error "out of bounds"
 * Used by 'checkSpotType'
 */

#define STATE_OUT_OF_BOUNDS 2

/* Return the piece type (PIECE_WHITE, PIECE_BLACK, PIECE_BLANK) */

int getPieceType(char c);

/*
 * Check that the piece on the spot (pieceX, pieceY) is of pieceType
 * If it is, return SDL_TRUE
 * If it is not, return SDL_FALSE
 * If it is out of bounds, return STATE_OUT_OF_BOUNDS
 */

int checkSpotType(int pieceX, int pieceY, int pieceType);

/* Clear availableMoves */

void clearAvailableMoves();

/*
 * Check one diagonal of a bishop's, rook's or queen's movement
 * coef1 and coef2 should be either 0, 1 or -1
 * The retrun value is weather the bishop's path ran into an opposite piece
 */

SDL_bool gameCheckLine(int boardX, int boardY, int coef1, int coef2, int pieceCollType, int* arrayToFill);

#endif

