
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 *
 * getPos64            -> Convert the X and Y into a single number from 0 to 63
 *
 * dispAvailableMoves  -> Self-explanatory
 * clearAvailableMoves -> Self-explanatory
 *
 * getPieceType        -> Return the piece type (WHITE, BLACK, BLANK);
 * gameGetMoves        -> Get all avalable moves for a piece on (boardX, boardY)
 */

#include <stdio.h>

#include "./include/game.h"
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

extern char tchs[64]; // -> tchs.c

int getPieceType(char c) {

	if ( (c == 'P') ||
		 (c == 'B') ||
		 (c == 'N') ||
		 (c == 'R') ||
		 (c == 'K') ||
		 (c == 'Q') )
		return PIECE_WHITE;

	else if ( (c == '.') ||
			  (c == '-') )
		return PIECE_BLANK;

	else
		return PIECE_BLACK;

};

extern int boardFlipped; // -> win.c

void clearAvailableMoves() {
	for (unsigned int i = 0; i < 64; i++)
		availableMoves[i] = 0;
}

void gameGetMoves(int boardX, int boardY) {

	boardX = boardX * (!boardFlipped) + (7 - boardX) * (boardFlipped);
	boardY = boardY * (!boardFlipped) + (7 - boardY) * (boardFlipped);

	clearAvailableMoves();

	switch (tchs[boardX + 8*boardY]) {

		case 'p':
			break;

		case 'b':
			break;

		case 'n':
			break;

		case 'r':

			// up
			for (int i = getPos64(boardX, boardY - 1); i >= 0; i -= 8) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
			}

			// down
			for (int i = getPos64(boardX, boardY + 1); i <= 64; i += 8) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
			}

			// left
			for (int i = getPos64(boardX - 1, boardY); i >= getPos64(0, boardY); i -= 1) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
			}

			// right
			for (int i = getPos64(boardX + 1, boardY); i <= getPos64(7, boardY); i += 1) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
			}

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

			// up
			for (int i = getPos64(boardX, boardY - 1); i >= 0; i -= 8) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
			}

			// down
			for (int i = getPos64(boardX, boardY + 1); i <= 64; i += 8) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
			}

			// left
			for (int i = getPos64(boardX - 1, boardY); i >= getPos64(0, boardY); i -= 1) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
			}

			// right
			for (int i = getPos64(boardX + 1, boardY); i <= getPos64(7, boardY); i += 1) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
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

