
/*
 * json.c - Functions relating to parsing JSON files and calling JSON objects
 *
 * Header: ./include/json.h
 */

#include <SDL2/SDL_pixels.h>

#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_util.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./include/config.h"
#include "./include/json.h"
#include "./include/path.h"

extern int   intTmp;   // -> tmp.c
extern char* charPTmp; // -> tmp.c

char  colorChars[6];

json_object* jsonColors;
json_object* jsonConfig;

extern char      pathBG     [PATH_TXT_LEN]; // -> win.c
extern char      pathBoard  [PATH_TXT_LEN]; // -> win.c
extern char      pathAMove  [PATH_TXT_LEN]; // -> win.c
extern char      pathB      [PATH_TXT_LEN]; // -> win.c
extern char      pathK      [PATH_TXT_LEN]; // -> win.c
extern char      pathN      [PATH_TXT_LEN]; // -> win.c
extern char      pathP      [PATH_TXT_LEN]; // -> win.c
extern char      pathQ      [PATH_TXT_LEN]; // -> win.c
extern char      pathR      [PATH_TXT_LEN]; // -> win.c
extern char      pathb      [PATH_TXT_LEN]; // -> win.c
extern char      pathk      [PATH_TXT_LEN]; // -> win.c
extern char      pathn      [PATH_TXT_LEN]; // -> win.c
extern char      pathp      [PATH_TXT_LEN]; // -> win.c
extern char      pathq      [PATH_TXT_LEN]; // -> win.c
extern char      pathr      [PATH_TXT_LEN]; // -> win.c
extern char      pathFont   [PATH_TXT_LEN]; // -> win.c
extern SDL_Color colorFont;                 // -> win.c

char* paths[16][3] = {

	{ pathBG,    "bgImage",    "img/background/%s.png" },
	{ pathBoard, "boardImage", "img/board/%s.png"      },
	{ pathAMove, "move",       "img/move/%s.png"       },
	{ pathB,     "pieceImage", "img/piece/%s/B.png"    },
	{ pathK,     "pieceImage", "img/piece/%s/K.png"    },
	{ pathN,     "pieceImage", "img/piece/%s/N.png"    },
	{ pathP,     "pieceImage", "img/piece/%s/P.png"    },
	{ pathQ,     "pieceImage", "img/piece/%s/Q.png"    },
	{ pathR,     "pieceImage", "img/piece/%s/R.png"    },
	{ pathb,     "pieceImage", "img/piece/%s/b.png"    },
	{ pathk,     "pieceImage", "img/piece/%s/k.png"    },
	{ pathn,     "pieceImage", "img/piece/%s/n.png"    },
	{ pathp,     "pieceImage", "img/piece/%s/p.png"    },
	{ pathq,     "pieceImage", "img/piece/%s/q.png"    },
	{ pathr,     "pieceImage", "img/piece/%s/r.png"    },
	{ pathFont,  "font",       "font/%s"               }

};

int jsonLoadConf() {

	charPTmp = addToGlobalPath(PATH_JSON_CONF);

	if (!access(charPTmp, F_OK)) {

		jsonConfig = json_object_from_file(charPTmp);
		printf("Log (json.c): JSON object at %s loaded successfully.\n", charPTmp);
		intTmp = EXIT_SUCCESS;

	} else {

		printf("Log (json.c): JSON object at %s couldn't be loaded.\n", charPTmp);
		intTmp = EXIT_FAILURE;

	}

	free(charPTmp);
	return intTmp;

}

int textLoadLocal(
		char* key, struct json_object *val, char* pathVar, char* keycmp,
		const char* pathToFile, const char* msgSuccess, const char* msgFailure
		) {

	if ( !strcmp(key, keycmp) ) {

		sprintf(pathVar, pathToFile, json_object_get_string(val));

		charPTmp = addToGlobalPath(pathVar);
		strcpy(pathVar, charPTmp);

		if (access(pathVar, F_OK) == 0) {

			printf(msgSuccess, pathVar);
			free(charPTmp);

		} else {

			printf(msgFailure, pathVar, key);
			return EXIT_FAILURE;

		}

	}

	return EXIT_SUCCESS;

}

int colorLoadLocal(
		SDL_Color* clr,
		const char* clrCode, int clrCodeLen,
		const char* clrJsonName
		) {

	if (clrCodeLen == 4) {
		colorChars[0] = clrCode[1]; colorChars[1] = clrCode[1];
		colorChars[2] = clrCode[2]; colorChars[3] = clrCode[2];
		colorChars[4] = clrCode[3]; colorChars[5] = clrCode[3];
	}

	else if (clrCodeLen == 7) {
		colorChars[0] = clrCode[1];
		colorChars[1] = clrCode[2];
		colorChars[2] = clrCode[3];
		colorChars[3] = clrCode[4];
		colorChars[4] = clrCode[5];
		colorChars[5] = clrCode[6];
	}
	else {
		printf("Log (json.c): The color for '%s' couldn't load. Check that the format for the color is good in conf.json.\n", clrJsonName);
		return EXIT_FAILURE;
	}

	clr->r = 0; clr->g = 0; clr->b = 0; clr->a = 255;

	for (unsigned int i = 0; i < 6; i++) {

		switch (colorChars[i]) {

			case '0': intTmp = 0;  break; case '1': intTmp = 1;  break;
			case '2': intTmp = 2;  break; case '3': intTmp = 3;  break;
			case '4': intTmp = 4;  break; case '5': intTmp = 5;  break;
			case '6': intTmp = 6;  break; case '7': intTmp = 7;  break;
			case '8': intTmp = 8;  break; case '9': intTmp = 9;  break;
			case 'A': intTmp = 10; break; case 'a': intTmp = 10; break;
			case 'B': intTmp = 11; break; case 'b': intTmp = 11; break;
			case 'C': intTmp = 12; break; case 'c': intTmp = 12; break;
			case 'D': intTmp = 13; break; case 'd': intTmp = 13; break;
			case 'E': intTmp = 14; break; case 'e': intTmp = 14; break;
			case 'F': intTmp = 15; break; case 'f': intTmp = 15; break;

			default:
				printf("Log (json.c): The color for '%s' couldn't load. Check for invalid characters in conf.json.\n", clrJsonName);
				return EXIT_FAILURE; break;

		}

		intTmp = intTmp * (i % 2) + intTmp*16 * !(i%2);

		clr->r += ((i == 0) + (i == 1))*intTmp;
		clr->g += ((i == 2) + (i == 3))*intTmp;
		clr->b += ((i == 4) + (i == 5))*intTmp;

	}

	printf("Log (json.c): The color for '%s' loaded successfully.\n", clrJsonName);
	return EXIT_SUCCESS;

}

// TODO: Check that namestrings aren't too large
// TODO: Check what happens with duplicate key objects in conf.json

int jsonAssetLoad() {

	json_object_object_foreach(jsonConfig, key, val) {

		for (unsigned int i = 0; i < 16; i++) {

			if (textLoadLocal(
				key, val,
				paths[i][0], paths[i][1], paths[i][2],
				"Log (json.c): %s loaded successfully.\n",
				"Log (json.c): %s couldn't load. Check '%s' in conf.json.\n"
				)) return EXIT_FAILURE;

		}

		if (!strcmp(key, "colors")) {

			jsonColors = json_object_object_get(jsonConfig, "colors");

			json_object_object_foreach(jsonColors, key, val) {

				colorLoadLocal(&colorFont, json_object_get_string(val), json_object_get_string_len(val), key);

			}

		}

	}

	return EXIT_SUCCESS;

}

