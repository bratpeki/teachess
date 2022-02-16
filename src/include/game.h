
#ifndef H_TEACHESS_GAME
#define H_TEACHESS_GAME

#define PIECE_BLACK 0
#define PIECE_WHITE 1
#define PIECE_BLANK 2

// Individual piece value, king's value is infinity (represented as 0)

#define VALUE_P 1
#define VALUE_B 3
#define VALUE_N 3
#define VALUE_R 5
#define VALUE_Q 9
#define VALUE_K 0

#define getPos64(x, y) (x + 8*(y))

// Get all avalable moves for a piece on (boardX, boardY) and store them in availableMoves

void gameGetMoves(int boardX, int boardY);

#endif

