
/*
 * global.c - Global functions and varibles called via 'extern'
 *
 * stateRunning -> A boolean-like integer whose values
 *                 are 1 (RUNNING) and 0 (NOT RUNNING)
 */

#include <json-c/json.h>

int          stateRunning = 0;
json_object* jsonConfig   = NULL;

