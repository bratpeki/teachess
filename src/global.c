
/*
 * global.c - Global functions and varibles called via 'extern'
 *
 * stateRunning -> A boolean-like integer whose values
 *                 are 1 (RUNNING) and 0 (NOT RUNNING)
 */

#include <SDL2/SDL.h>
#include <json-c/json.h>

SDL_Texture*  textB;
SDL_Texture*  textBG;
SDL_Texture*  textBoard;
SDL_Texture*  textK;
SDL_Texture*  textN;
SDL_Texture*  textP;
SDL_Texture*  textQ;
SDL_Texture*  textR;

int          stateRunning = 0;

json_object* jsonConfig   = NULL;

