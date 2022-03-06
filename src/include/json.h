
#ifndef H_TEACHESS_JSON
#define H_TEACHESS_JSON

#include <SDL2/SDL_pixels.h>

#include "json-c/json.h"

/* Load the JSON file into the global json_object 'jsonConfig' */

int jsonLoadConf();

/*
 * Handle checking JSON strings and applying their value to
 * their outputs (extern chars)
 */

int textLoadLocal(
		char* key, struct json_object* val, char* pathVar, char* keycmp,
		const char* pathToFile, const char* msgSuccess, const char* msgFailure
		);

/* Take the text from clrCode and apply the RGB values to the clr struct */

int colorLoadLocal(
		SDL_Color* clr,
		const char* clrCode, int clrCodeLen,
		const char* clrJsonName
		);

/* Load the JSON data into their assorted SDL_Texture objects */

int jsonAssetLoad();

#endif

