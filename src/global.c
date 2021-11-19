
/*
 * global.c - Global functions and varibles called via 'extern'
 *
 * pathProg     -> The path to the program
 * stateRunning -> A boolean-like integer whose values
 *                 are 1 (RUNNING) and 0 (NOT RUNNING)
 * jsonConfig   -> The JSON configuration file
 */

#include <json-c/json.h>

char*        pathProg     = NULL;

int          stateRunning = 0;

json_object* jsonConfig   = NULL;

