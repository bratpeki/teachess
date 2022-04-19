
#ifndef H_TEACHESS_GAME
#define H_TEACHESS_GAME

#define PIECE_BLACK 0
#define PIECE_WHITE 1
#define PIECE_BLANK 2

/* Individual piece value, king's value is infinity (represented as 0) */

#define VALUE_P 1
#define VALUE_B 3
#define VALUE_N 3
#define VALUE_R 5
#define VALUE_Q 9
#define VALUE_K 0

#define getPos64(x, y) (x + 8*(y))

/*
 * Get all avalable moves for a piece on (boardX, boardY)
 * Store them in availableMoves
 */

void gameGetMoves(int boardX, int boardY);

/*
 * Convert piece movement for (x1, y1) to (x2, y2) into proper game notatio
 * Store the notation in currentNotation
 */

void gameGetNotation(int x1, int y1, int x2, int y2);

#endif

