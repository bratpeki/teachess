
/*
 * json.c - Functions relating to parsing JSON files and calling JSON objects
 *
 * Header: ./include/json.h
 *
 * jsonLoad     -> Load the JSON file into the global json_object 'jsonConfig'
 * jsonTextLoad -> Load the JSON data into their assorted SDL_Texture objects
 */

#include <json-c/json.h>
#include <json-c/json_util.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./include/config.h"
#include "./include/json.h"
#include "./include/path.h"

char *tmp;

json_object* jsonConfig;

int jsonLoad(char* pathToConfig) {

	tmp = addToGlobalPath(pathToConfig);

	if (!access(tmp, F_OK)) {

		jsonConfig = json_object_from_file(tmp);
		printf("Log: JSON object at %s loaded successfully.\n", tmp);

	} else {

		printf("Log: JSON object at %s couldn't be loaded.\n", tmp);
		free(tmp);
		return 1;

	}

	free(tmp);
	return 0;

}

// TODO: Check that namestrings aren't too large
// TODO: Implement the pathing function on the pawn textures

int jsonTextLoad(char *pathBG, char *pathBoard, char *pathPiece) {

	json_object_object_foreach(jsonConfig, key, val) {

		// THE CHESS BOARD IMAGE

		if ( !strcmp(key, "boardImage")) {

			sprintf(pathBoard, "img/board/%s.png", json_object_get_string(val));

			tmp = addToGlobalPath(pathBoard);
			strcpy(pathBoard, tmp);

			if ( access(pathBoard, F_OK) == 0 ) {

				printf("Log: Board image at %s loaded successfully.\n", pathBoard);
				free(tmp);

			} else {

				printf("Log: Board image couldn't be loaded. Check that the name from 'boardImage' in conf.json is correct.\n");
				free(tmp);
				return 1;

			}

		}

		// THE BACKGROUND IMAGE

		if ( !strcmp(key, "bgImage")) {

			sprintf(pathBG, "img/background/%s.png", json_object_get_string(val));

			tmp = addToGlobalPath(pathBG);
			strcpy(pathBG, tmp);

			if ( access(pathBG, F_OK) == 0 ) {

				printf("Log: Background image at %s loaded successfully.\n", pathBG);
				free(tmp);

			} else {

				printf("Log: Background image couldn't be loaded. Check that the name from 'bgImage' in conf.json is correct.\n\n");
				free(tmp);
				return 1;

			}

		}

		// THE CHESS PIECES

	}

	return 0;

}

