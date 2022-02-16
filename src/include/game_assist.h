
#ifndef H_TEACHESS_GAME_ASSIST
#define H_TEACHESS_GAME_ASSIST

// Check that the sport on (spotX, spotY) is free for the piece to step on

int checkSpotType(int pieceX, int pieceY, int pieceType);

// Return true/false based on if the piece type matches the specified

int getPieceType(char c);

// Clear availableMoves

void clearAvailableMoves();

/*
 * Check one diagonal of a bishop's movement
 * coef1 and coef2 ought to be either 1 or -1
 */

void bishopCheckDiagonal(int boardX, int boardY, int coef1, int coef2, int pieceCollType);

#endif

