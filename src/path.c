
/*
 * path.c - Handle filepaths
 *
 * Header: ./include/path.h
 */

#include "./include/path.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int countSlash = 0;
unsigned int tmpCountSlash = 0;

extern char* pathProg; // -> main.c

void setGlobalPath(char* src) {

	for (unsigned int i = 0; i < strlen(src); i++)
		if (src[i] == '/')
			countSlash++;

	for (unsigned int i = 0; i < strlen(src); i++) {

		if (src[i] == '/') {

			tmpCountSlash++;

			if (tmpCountSlash == countSlash) {

				pathProg = (char*)calloc(i + 1, sizeof(char));
				memcpy(pathProg, src, i + 1);

			}

		}

	}

}

char* addToGlobalPath(char* src) {

	char* out = (char*)calloc(strlen(pathProg) + strlen(src) + 1, sizeof(char));

	sprintf(out, "%s%s", pathProg, src);

	return out;

}

