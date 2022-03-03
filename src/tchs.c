
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

char tchsTitle[PATH_TXT_LEN] = "TeaChess";

int k, K;

int tchsTitleLen = 8;

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

char pieceLegal[18] = {
	'-', '.',
	'b', 'B', 'c', 'C',
	'e', 'E', 'k', 'K',
	'n', 'N', 'p', 'P',
	'q', 'Q', 'r', 'R'
};

int pieceLegalCheck(char piece) {

	for (unsigned int i = 0; i < 18; i++)
		if (piece == pieceLegal[i]) return SDL_TRUE;

	return SDL_FALSE;

}

// TODO: Better checking before loading the file
//       Check for lenght being exactly 63 characters, correct pieces and no two-king situations
//       Then load everything

int tchsRead(char* name) {

	FILE* fp;
	char* ctchs;
	char* gptchs;
	char  ptchs[PATH_TXT_LEN];
	int   tchsLen;

	k = 0; K = 0;

	snprintf(ptchs, PATH_TXT_LEN, "tchs/%s.tchs", name);

	gptchs = addToGlobalPath(ptchs);

	fp = fopen(gptchs, "rb");

	if (!fp) {
		printf ("Log (tchs.c): %s couldn't load.\n", ptchs);
		return EXIT_FAILURE;
	}

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

	fseek(fp, 0, SEEK_END);
	tchsLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	ctchs = malloc(tchsLen);
	fread(ctchs, 1, tchsLen - sizeof(char), fp);

	int tchsCount = 0;

	for (unsigned int i = 0; i < tchsLen - sizeof(char); i++) {

		if (pieceLegalCheck(ctchs[i]) == SDL_FALSE) {
			if ( (ctchs[i] != '\n') && (ctchs[i] != '\0') ) {
				printf("Log (tchs.c): Unknown char in %s (%c)\n", gptchs, ctchs[i]);
				return EXIT_FAILURE;
			}
		}

		else {

			if (tchsCount > 64) {
				printf("Log (tchs.c): %s 64 characters of interest surpassed\n", gptchs);
				return EXIT_FAILURE;
			}
			else {
				k += (ctchs[i] == 'k') || (ctchs[i] == 'c');
				K += (ctchs[i] == 'K') || (ctchs[i] == 'C');
				tchs[tchsCount++] = ctchs[i];
			}

		}

	}

	clearAvailableMoves();

	fclose(fp);
	free(ctchs);
	free(gptchs);

	return EXIT_SUCCESS;

}

