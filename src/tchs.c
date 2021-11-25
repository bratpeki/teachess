
/*
 * tchs.c - Load and handle TCHS files
 *
 * Header: ./include/tchs.h
 *
 * tchsRead -> Read a TCHS file and return the exit code
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/config.h"
#include "./include/path.h"

/*
 *  tchs    - The TCHS file content
 *  tchsLen - The TCHS file string lenght
 * ftchs    - The TCHS file
 * ptchs    - The TCHS file path
 */

int   tchsLen;
char *tchs;

int tchsRead(char *name) {

	char *ptchs = (char*)calloc(sizeof(char), PATH_TEXT_LENGHT);

	sprintf(ptchs, "tchs/%s.tchs", name);
	ptchs = addToGlobalPath(ptchs);

	FILE *ftchs = fopen(ptchs, "r");

	if (!ftchs) {
		printf ("Log (tchs.c): %s couldn't load.\n", ptchs);
		return 1;
	}

	fseek(ftchs, 0, SEEK_END);
		tchsLen = ftell(ftchs);
	rewind(ftchs);

	tchs = malloc(tchsLen);
	fread(tchs, sizeof(char), tchsLen, ftchs);

	printf("%s\n", tchs);

	fclose(ftchs);
	free(ptchs);

	return 0;

}

