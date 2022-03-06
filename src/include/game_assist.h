
#ifndef H_TEACHESS_GAME_ASSIST
#define H_TEACHESS_GAME_ASSIST

/* Return the piece type */

int getPieceType(char c);

/* Check that the spot on (spotX, spotY) is of pieceType */

int checkSpotType(int pieceX, int pieceY, int pieceType);

/* Clear availableMoves */

void clearAvailableMoves();

/*
 * Check one diagonal of a bishop's, rook's or queen's movement
 * coef1 and coef2 should be either 1 or -1
 */

void gameCheckLine(int boardX, int boardY, int coef1, int coef2, int pieceCollType);

#endif

