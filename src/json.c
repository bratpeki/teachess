
/*
 * json.c - Functions relating to parsing JSON files and calling JSON objects
 *
 * Header: ./include/json.h
 *
 * jsonLoadConf  -> Load the JSON file into the global json_object 'jsonConfig'
 *                  Returns 0 (success) or 1 (failure)
 * textLoadLocal -> Handle checking JSON strings and applying their value to
 *                  their outputs (extern chars)
 *                  Returns 0 (success) or 1 (failure)
 * jsonTextLoad  -> Load the JSON data into their assorted SDL_Texture objects
 *                  Returns 0 (success) or 1 (failure)
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

extern char pathBG    [PATH_TXT_LEN]; // -> win.c
extern char pathBoard [PATH_TXT_LEN]; // -> win.c
extern char pathAMove [PATH_TXT_LEN]; // -> win.c
extern char pathB     [PATH_TXT_LEN]; // -> win.c
extern char pathK     [PATH_TXT_LEN]; // -> win.c
extern char pathN     [PATH_TXT_LEN]; // -> win.c
extern char pathP     [PATH_TXT_LEN]; // -> win.c
extern char pathQ     [PATH_TXT_LEN]; // -> win.c
extern char pathR     [PATH_TXT_LEN]; // -> win.c
extern char pathb     [PATH_TXT_LEN]; // -> win.c
extern char pathk     [PATH_TXT_LEN]; // -> win.c
extern char pathn     [PATH_TXT_LEN]; // -> win.c
extern char pathp     [PATH_TXT_LEN]; // -> win.c
extern char pathq     [PATH_TXT_LEN]; // -> win.c
extern char pathr     [PATH_TXT_LEN]; // -> win.c
extern char pathFont  [PATH_TXT_LEN]; // -> win.c

char *paths[16][3] = {

	{ pathBG,    "bgImage",    "img/background/%s.png" },
	{ pathBoard, "boardImage", "img/board/%s.png"      },
	{ pathAMove, "move",       "img/move/%s.png"       },
	{ pathB,     "pieceImage", "img/piece/%s/B.png"    },
	{ pathK,     "pieceImage", "img/piece/%s/K.png"    },
	{ pathN,     "pieceImage", "img/piece/%s/N.png"    },
	{ pathP,     "pieceImage", "img/piece/%s/P.png"    },
	{ pathQ,     "pieceImage", "img/piece/%s/Q.png"    },
	{ pathR,     "pieceImage", "img/piece/%s/R.png"    },
	{ pathb,     "pieceImage", "img/piece/%s/b.png"    },
	{ pathk,     "pieceImage", "img/piece/%s/k.png"    },
	{ pathn,     "pieceImage", "img/piece/%s/n.png"    },
	{ pathp,     "pieceImage", "img/piece/%s/p.png"    },
	{ pathq,     "pieceImage", "img/piece/%s/q.png"    },
	{ pathr,     "pieceImage", "img/piece/%s/r.png"    },
	{ pathFont,  "font",       "font/%s"               }

};

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

			printf(msgFailure, pathVar, key);
			return 1;

		}

	}

	return 0;

}

// TODO: Check that namestrings aren't too large
// TODO: Check what happens with duplicate key objects in conf.json

int jsonTextLoad() {

	json_object_object_foreach(jsonConfig, key, val) {

		for (unsigned int i = 0; i < 16; i++) {

			if (textLoadLocal(
				key, val,
				paths[i][0], paths[i][1], paths[i][2],
				"Log (json.c): %s loaded successfully.\n",
				"Log (json.c): %s couldn't load. Check '%s' in conf.json.\n"
				)) return 1;

		}

	}

	return 0;

}

