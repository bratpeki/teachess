
#ifndef H_TEACHESS_TCHS
#define H_TEACHESS_TCHS

#define EXIT_BAD_FILENAME 2
#define EXIT_BADNUM_KINGS 3
#define EXIT_BADNUM_CHARS 4

/* Read a TCHS file and return the exit code */

int tchsRead(char* name);

/* Check if a piece is legal */

int pieceLegalCheck(char piece);

#endif

