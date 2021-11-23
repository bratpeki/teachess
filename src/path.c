
/*
 * path.c - Handle filepaths
 *
 * Header: ./include/path.h
 *
 * setGlobalPath   -> Set the global variable pathProg
 * addToGlobalPath -> Add the src to pathProg and return the output
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/path.h"

unsigned int countSlash = 0;
unsigned int tmpCountSlash = 0;

extern char* pathProg; // -> main.c

void setGlobalPath(char *src) {

	for (unsigned int i = 0; i < strlen(src); i++)
		if (src[i] == '/')
			countSlash++;

	for (unsigned int i = 0; i < strlen(src); i++) {

		if (src[i] == '/') {

			tmpCountSlash++;

			if (tmpCountSlash == countSlash) {

				pathProg = (char*)calloc(sizeof(char), i + 1);
				memcpy(pathProg, src, i + 1);

			}

		}

	}

}

char *addToGlobalPath(char *src) {

	char *out = (char*)calloc(sizeof(char), strlen(pathProg) + strlen(src));

	sprintf(out, "%s%s", pathProg, src);

	return out;

}

