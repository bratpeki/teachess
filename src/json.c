
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

extern json_object* jsonConfig;

int jsonLoad(char* pathToConfig) {

	if (!access(pathToConfig, F_OK)) {
		jsonConfig = json_object_from_file(pathToConfig);
		printf("Log: %s loaded successfully.\n", PATH_JSON_CONFIG);
	}

	else {
		printf("Log: %s couldn't be loaded.", PATH_JSON_CONFIG);
		return 1;
	}

	return 0;

}

// TODO: Check that namestring aren't too large

int jsonTextLoad(char *pathBG, char *pathBoard, char *pathPiece) {

	json_object_object_foreach(jsonConfig, key, val) {

		// THE CHESS BOARD IMAGE

		if ( !strcmp(key, "boardImage")) {

			sprintf(pathBoard, "./img/board/%s.png", json_object_get_string(val));

			if ( access(pathBoard, F_OK) == 0 ) {
				printf("Log: Board image loaded successfully.\n");
			}

			else {
				printf("Log: Board image loaded unsuccessfully.\n");
				printf("Log: Check that the name from 'boardImage' in conf.json is correct.\n");
				return 1;
			}

		}

		// THE BACKGROUND IMAGE

		if ( !strcmp(key, "bgImage")) {

			sprintf(pathBG, "./img/background/%s.png", json_object_get_string(val));

			if ( access(pathBG, F_OK) == 0 ) {
				printf("Log: Background image loaded successfully.\n");
			}
			else {
				printf("Log: Background image loaded unsuccessfully.\n");
				printf("Log: Check that the name from 'bgImage' in conf.json is correct.\n");
				return 1;
			}

		}

		// THE CHESS PIECES
	}

	return 0;

}

