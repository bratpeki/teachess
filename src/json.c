
/*
 * json.c - Functions relating to parsing JSON files and calling JSON objects
 *
 * Header: ./include/json.h
 *
 * jsonLoadConf -> Load the JSON file into the global json_object 'jsonConfig'
 * jsonTextLoad -> Load the JSON data into their assorted SDL_Texture objects
 */

#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_util.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./include/config.h"
#include "./include/json.h"
#include "./include/path.h"

char *tmp;

json_object* jsonConfig;

extern char pathBG    [PATH_TEXT_LENGHT]; // -> win.c
extern char pathBoard [PATH_TEXT_LENGHT]; // -> win.c
extern char pathPiece [PATH_TEXT_LENGHT]; // -> win.c

extern char pathB     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathK     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathN     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathP     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathQ     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathR     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathb     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathk     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathn     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathp     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathq     [PATH_TEXT_LENGHT]; // -> win.c
extern char pathr     [PATH_TEXT_LENGHT]; // -> win.c

int jsonLoadConf() {

	tmp = addToGlobalPath(PATH_JSON_CONF);

	if (!access(tmp, F_OK)) {

		jsonConfig = json_object_from_file(tmp);
		printf("Log (json.c): JSON object at %s loaded successfully.\n", tmp);

	} else {

		printf("Log (json.c): JSON object at %s couldn't be loaded.\n", tmp);
		free(tmp);
		return 1;

	}

	free(tmp);
	return 0;

}

int textLoadLocal(
		char *key, struct json_object *val, char *pathVar, char *keycmp,
		const char *pathToFile, const char *msgSuccess, const char *msgFailure
		) {

	if ( !strcmp(key, keycmp) ) {

		sprintf(pathVar, pathToFile, json_object_get_string(val));

		tmp = addToGlobalPath(pathVar);
		strcpy(pathVar, tmp);

		if ( access(pathVar, F_OK) == 0 ) {

			printf(msgSuccess, pathVar);
			free(tmp);

		} else {

			printf("%s", msgFailure);
			free(tmp);
			return 1;

		}

	}

	return 0;

}

// TODO: Check that namestrings aren't too large
// TODO: Implement the pathing function on the pawn textures

int jsonTextLoad() {

	json_object_object_foreach(jsonConfig, key, val) {

		// THE BACKGROUND IMAGE

		if (textLoadLocal(
			key, val, pathBG, "bgImage",
			"img/background/%s.png",
			"Log (json.c): Background image at %s loaded successfully.\n",
			"Log (json.c): Background image couldn't be loaded. Check that the name from 'bgImage' in conf.json is correct.\n\n"
			) == 1) return 1;

		// THE CHESS BOARD IMAGE

		if (textLoadLocal(
			key, val, pathBoard, "boardImage",
			"img/board/%s.png",
			"Log (json.c): Board image at %s loaded successfully.\n",
			"Log (json.c): Board image couldn't be loaded. Check that the name from 'boardImage' in conf.json is correct.\n"
			) == 1) return 1;

		// THE CHESS PIECES

		if ( !strcmp(key, "pieceImage") ) {

			printf("Log (json.c): Piece theme is %s\n", json_object_get_string(val));

		}

	}

	return 0;

}

