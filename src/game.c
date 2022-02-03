
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 *
 * dispAvailableMoves  -> Self-explanatory
 * clearAvailableMoves -> Self-explanatory
 * gameGetMoves        -> Get all avalable moves for a piece on (boardX, boardY)
 * getPos64            -> Convert the X and Y into a single number from 0 to 63
 */

#include <stdio.h>

#include "./include/tchs.h"

#define getPos64(x, y) (x + 8*(y))

int gameTurn;
int piecePos64;

int availableMoves[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

extern int boardFlipped; // -> win.c

// SUBJECT TO LATER REMOVAL

void dispAvailableMoves() {
	for (unsigned int i = 0; i < 64; i++) {

		printf("%d", availableMoves[i]);

		if ((i+1) % 8 == 0) printf("%c", '\n');

	}
	printf("===\n");
}

void clearAvailableMoves() {
	for (unsigned int i = 0; i < 64; i++)
		availableMoves[i] = 0;
}

void gameGetMoves(int boardX, int boardY) {

	clearAvailableMoves();

	switch (tchsGetPiece(boardX, boardY, boardFlipped)) {

		case 'p':
			break;

		case 'b':
			break;

		case 'n':
			break;

		case 'r':
			break;

		case 'k':
			break;

		case 'q':
			break;

		case 'P':
			break;

		case 'B':
			break;

		case 'N':
			break;

		case 'R':

			// WORKING HERE
			// TODO: Check going through pieces

			// up
			for (int i = getPos64(boardX, boardY - 1); i >= 0; i -= 8) {
				availableMoves[i] = 1;
			}

			// down
			for (int i = getPos64(boardX, boardY + 1); i <= 64; i += 8) {
				availableMoves[i] = 1;
			}

			// left
			for (int i = getPos64(boardX - 1, boardY); i >= getPos64(0, boardY); i -= 1) {
				availableMoves[i] = 1;
			}

			// right
			for (int i = getPos64(boardX + 1, boardY); i <= getPos64(7, boardY); i += 1) {
				availableMoves[i] = 1;
			}

			break;

		case 'K':
			break;

		case 'Q':
			break;

		default:
			break;

	}

};

