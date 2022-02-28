
#ifndef H_TEACHESS_TCHS
#define H_TEACHESS_TCHS

#define EXIT_BAD_FILENAME   2
#define EXIT_MULTIPLE_KINGS 3

/*
 * Read a TCHS file and return the exit code (exit code output)
 */

int tchsRead(char* name);

/*
 * Check if a piece is legal (boolean output)
 */

int pieceLegalCheck(char piece);

#endif

