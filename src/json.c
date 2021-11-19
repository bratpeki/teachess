
/*
 * json.c - Functions relating to parsing JSON files and calling JSON objects
 *
 * Header: ./include/json.h
 */

#include <json-c/json.h>
#include <json-c/json_util.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./include/json.h"
#include "./include/log.h"

extern json_object* jsonConfig;

int jsonLoad(char* pathToConfig) {

	if (!access(pathToConfig, F_OK)) {
		jsonConfig = json_object_from_file(pathToConfig);
		dp("PATH_JSON_CONFIG loaded successfully.");
	}

	else {
		dp("PATH_JSON_CONFIG couldn't be loaded.");
		return 1;
	}

	return 0;

}

// Check and asign the JSON object values where they belong
// TODO:
//     check that namestring aren't too large

int jsonTextLoad(char *pathBG, char *pathBoard) {

	json_object_object_foreach(jsonConfig, key, val) {

		if ( !strcmp(key, "boardImage")) {

			sprintf(pathBoard, "./img/board/%s.png", json_object_get_string(val));

			if ( access(pathBoard, F_OK) == 0 ) {
				dp("Board image loaded successfully.");
			}

			else {
				dp("Board image loaded unsuccessfully.");
				dp("Check that the name from 'boardImage' in conf.json is correct.");
				return 1;
			}

		}

		if ( !strcmp(key, "bgImage")) {

			sprintf(pathBG, "./img/background/%s.png", json_object_get_string(val));

			if ( access(pathBG, F_OK) == 0 ) {
				dp("Background image loaded successfully.");
			}
			else {
				dp("Background image loaded unsuccessfully.");
				dp("Check that the name from 'bgImage' in conf.json is correct.");
				return 1;
			}

		}
	}

	return 0;

}

