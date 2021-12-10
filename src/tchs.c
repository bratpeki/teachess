
/*
 * tchs.c - Load and handle TCHS files
 *
 * Header: ./include/tchs.h
 *
 * pieceLegalCheck -> Check if a piece is legal
 * tchsRead        -> Read a TCHS file and return the exit code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/config.h"
#include "./include/path.h"

char tchs[64] = {
	'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
	'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'-', '-', '-', '-', '-', '-', '-', '-',
	'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
	'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R',
};

char pieceLegal[16] = {
	'-', '.', 'b', 'B',
	'e', 'E', 'k', 'K',
	'n', 'N', 'p', 'P',
	'q', 'Q', 'r', 'R'
};

int pieceLegalCheck(char piece) {

	for (unsigned int i = 0; i < 16; i++)
		if (piece == pieceLegal[i]) return 0;

	return 1;
}

int tchsRead(char *name) {

	FILE *fp;
	char *ctchs;
	char *gptchs;
	char  ptchs[PATH_TEXT_LENGHT];
	int   tchsLen;

	snprintf(ptchs, PATH_TEXT_LENGHT, "tchs/%s.tchs", name);

	gptchs = addToGlobalPath(ptchs);

	fp = fopen(gptchs, "rb");

	if (!fp) {
		printf ("Log (tchs.c): %s couldn't load.\n", ptchs);
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	tchsLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	ctchs = malloc(tchsLen);
	fread(ctchs, 1, tchsLen - sizeof(char), fp);

	int tchsCount = 0;

	for (unsigned int i = 0; i < tchsLen - sizeof(char); i++) {

		if (pieceLegalCheck(ctchs[i]) == 1) {
			if ( (ctchs[i] != '\n') && (ctchs[i] != '\0') ) {
				printf("Log (tchs.c): Unknown char in %s (%c)\n", gptchs, ctchs[i]);
				return 1;
			}
		}

		else {

			if (tchsCount > 64) {
				printf("Log (tchs.c): %s 64 characters of interest surpassed\n", gptchs);
				return 1;
			}
			else tchs[tchsCount++] = ctchs[i];

		}

	}

	fclose(fp);
	free(ctchs);
	free(gptchs);

	return 0;

}

