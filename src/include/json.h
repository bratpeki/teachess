
#ifndef H_TEACHESS_JSON
#define H_TEACHESS_JSON

#include "json-c/json.h"

/*
 * Load the JSON file into the global json_object 'jsonConfig'
 * Returns 0 (success) or 1 (failure)
 */

int jsonLoadConf();

/*
 * Handle checking JSON strings and applying their value to
 * their outputs (extern chars)
 * Returns 0 (success) or 1 (failure)
 */

int textLoadLocal(
		char* key, struct json_object *val, char* pathVar, char* keycmp,
		const char* pathToFile, const char* msgSuccess, const char* msgFailure
		);

/*
 * Load the JSON data into their assorted SDL_Texture objects
 * Returns 0 (success) or 1 (failure)
 */

int jsonTextLoad();

#endif

