
/*
 * tchs.c - Load and handle TCHS files
 *
 * Header: ./include/tchs.h
 */

#include <SDL2/SDL_stdinc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/config.h"
#include "./include/game.h"
#include "./include/game_assist.h"
#include "./include/path.h"
#include "./include/tchs.h"

extern int gameTurn;  // -> game.c
extern int minOffset; // -> win.c
extern int offset;    // -> win.c
extern int intTmp;    // -> tmp.c

char tchsTitle[PATH_TXT_LEN] = "TeaChess";
int  tchsTitleLen            = 8;

char tchs[64] = {
	'r', 'n', 'b', 'q', 'c', 'b', 'n', 'r',
	'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	'R', 'N', 'B', 'Q', 'C', 'B', 'N', 'R',
};

/*
 * Piece list:
 * -/. - Empty space
 * b/B - Bishop
 * c/C - Castle-able king
 * e/E - "En passant"-able pawn
 * k/K - King
 * n/N - Knight
 * p/P - Pawn
 * q/Q - Queen
 * r/R - Rook
 */

char pieceLegal[22] = {
	'-', '.',
	'B', 'C', 'E', 'K', 'N', 'P', 'Q', 'R', 'X', 'Y',
	'b', 'c', 'e', 'k', 'n', 'p', 'q', 'r', 'x', 'y'
};

int pieceLegalCheck(char piece) {

	for (unsigned int i = 0; i < 22; i++)
		if (piece == pieceLegal[i]) return SDL_TRUE;

	return SDL_FALSE;

}

FILE* fp;                  // TCHS File contents
char  ptchs[PATH_TXT_LEN]; // Path to the TCHS
char* ctchs;               // TCHS characters
char* gptchs;              // Global path to the TCHS
int   k, K;                // King counters
int   tchsLen;             // Lenght of the TCHS file, character-wise
int   tchsCount;           // TCHS character count

int tchsRead(char* name) {

	k = 0; K = 0; tchsCount = 0;

	snprintf(ptchs, PATH_TXT_LEN, "tchs/%s.tchs", name);

	gptchs = addToGlobalPath(ptchs);

	fp = fopen(gptchs, "rb");

	if (!fp) {
		printf ("Log (tchs.c): %s couldn't load.\n", ptchs);
		free(gptchs);
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_END);
	tchsLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	ctchs = malloc(tchsLen);
	fread(ctchs, 1, tchsLen - sizeof(char), fp);

	for (unsigned int i = 0; i < tchsLen; i++) {

		if ( !pieceLegalCheck(ctchs[i]) ) {

			if ( (ctchs[i] != '\n') && (ctchs[i] != '\0') ) {
				printf("Log (tchs.c): Unknown char in %s (%c)\n", gptchs, ctchs[i]);
				free(gptchs); free(ctchs);
				return EXIT_FAILURE;
			}

		}

		else {

			if (tchsCount > 64) {
				printf("Log (tchs.c): %s 64 characters of interest surpassed\n", gptchs);
				return EXIT_FAILURE;
			}
			else {
				k += (ctchs[i] == 'k') || (ctchs[i] == 'c') || (ctchs[i] == 'x') || (ctchs[i] == 'y');
				K += (ctchs[i] == 'K') || (ctchs[i] == 'C') || (ctchs[i] == 'X') || (ctchs[i] == 'Y');
				tchs[tchsCount++] = ctchs[i];
			}

		}

	}

	if ( (k != 1) || (K != 1) ) {
		printf("Log (tchs.c): Number of kings unsatisfactory. Check %s\n", gptchs);
		free(gptchs); free(ctchs);
		return EXIT_BADNUM_KINGS;
	}

	if (tchsCount != 64) {
		printf("Log (tchs.c): Number of characters isn't 64. Check %s\n", gptchs);
		free(gptchs); free(ctchs);
		return EXIT_BADNUM_CHARS;
	}

	clearAvailableMoves();

	minOffset = 1;
	offset = 1;
	for (unsigned int i = 0; i < PATH_TXT_LEN; i++) tchsTitle[i] = ' ';
	strcpy(tchsTitle, name);

	tchsTitleLen = strlen(name);

	switch (name[0]) {
		case 'b': gameTurn = PIECE_BLACK; break;
		case 'w': gameTurn = PIECE_WHITE; break;
		default:
			free(gptchs);
			return EXIT_BAD_FILENAME;
	}

	fclose(fp);
	free(ctchs);
	free(gptchs);

	return EXIT_SUCCESS;

}

