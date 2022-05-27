
/*
 * event.c - Handle events
 *
 * Header: event.h
 */

#include "include/event.h"
#include "include/game.h"
#include "include/game_assist.h"
#include "include/tchs.h"
#include "include/win.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_stdinc.h>

#include <stdio.h>

extern SDL_bool boardFlipped;       // -> win.c
extern SDL_bool stateRunning;       // -> main.c
extern char     tchs[64];           // -> tchs.c
extern int      availableMoves[64]; // -> game.c
extern int      gameTurn;           // -> game.c
extern int      minOffset;          // -> win.c
extern int      offset;             // -> win.c

SDL_Event event;
int       boardX, boardY;
int       boardXPrev, boardYPrev;
int       currPieceType;
int       mouseX, mouseY = 0;

// TODO: Organize the event handler better and check for performance optimizations

void eventHandle() {

	if (!SDL_WaitEvent(&event)) return;

	SDL_GetMouseState(&mouseX, &mouseY);

	switch (event.type) {

		case SDL_QUIT: stateRunning = SDL_FALSE; break;

		case SDL_MOUSEBUTTONDOWN:

			if ((mouseX < 104)&&(mouseX > 616)&&(mouseY < 104)&&(mouseY > 616)) return;

			boardX = (int)((mouseX - 104) / 64); boardX = boardX * (!boardFlipped) + (7 - boardX) * (boardFlipped);
			boardY = (int)((mouseY - 104) / 64); boardY = boardY * (!boardFlipped) + (7 - boardY) * (boardFlipped);

			currPieceType = getPieceType(tchs[getPos64(boardX, boardY)]);

			if (currPieceType == gameTurn) {

				gameGetMoves(boardX, boardY);

				boardXPrev = boardX;
				boardYPrev = boardY;

			}

			if (
				(currPieceType == !gameTurn) ||
				(currPieceType == PIECE_BLANK)
			) {

				if (availableMoves[getPos64(boardX, boardY)] == 1) {

					clearAvailableMoves();

					gameGetNotation(boardXPrev, boardYPrev, boardX, boardY);

					tchs[getPos64(boardX, boardY)] = tchs[getPos64(boardXPrev, boardYPrev)];
					tchs[getPos64(boardXPrev, boardYPrev)] = '-';

					// TODO: Check if a piece is giving a check here

					gameTurn = !gameTurn;

				}

			}

			break;

		case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {

			case SDLK_ESCAPE: stateRunning = SDL_FALSE; break;

			case SDLK_f: boardFlipped = !boardFlipped; break;

			case SDLK_a: offset--;           break;
			case SDLK_d: offset++;           break;
			case SDLK_s: offset = minOffset; break;

			case SDLK_1:
				tchsRead("wDefault");
				break;

			case SDLK_2:
				tchsRead("bRuy Lopez Mainline (5 Moves)");
				break;

			case SDLK_3:
				tchsRead("wRook Endgame Example");
				break;

			case SDLK_4:
				tchsRead("wExample");
				break;

		}

	}

	winRender();

}

