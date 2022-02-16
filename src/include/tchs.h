
#ifndef H_TEACHESS_TCHS
#define H_TEACHESS_TCHS

/*
 * Read a TCHS file and return the exit code (exit code output)
 * Returns 0 (success), 1 (failure) or 2 (bad filename)
 */

int tchsRead(char *name);

/*
 * Check if a piece is legal (boolean output)
 * Returns 0 (false) or 1 (true)
 */

int pieceLegalCheck(char piece);

#endif

