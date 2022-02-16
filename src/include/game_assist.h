
#ifndef H_TEACHESS_GAME_ASSIST
#define H_TEACHESS_GAME_ASSIST

// Check that the sport on (spotX, spotY) is free for the piece to step on

int checkSpotType(int pieceX, int pieceY, int pieceType);

// Return true/false based on if the piece type matches the specified

int getPieceType(char c);

// Clear availableMoves

void clearAvailableMoves();

#endif

