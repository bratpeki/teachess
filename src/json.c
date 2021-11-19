
/*
 * json.c - Functions relating to parsing JSON files and callic JSON objects
 *
 * Header: ./include/json.h
 */

#include <json-c/json.h>
#include <json-c/json_util.h>

#include <unistd.h>

#include "./include/json.h"

extern json_object* jsonConfig;

int jsonLoad(char* pathToConfig) {

	if ( access( pathToConfig, F_OK) == 0 ) jsonConfig = json_object_from_file(pathToConfig);
	else                                    return 1;

	return 0;

}

