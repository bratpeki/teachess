
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
		 (c == 'E') ||
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

// TODO: King movement rework
// TODO: Bishop, knight, queen

void gameGetMoves(int boardX, int boardY) {

	boardX = boardX * (!boardFlipped) + (7 - boardX) * (boardFlipped);
	boardY = boardY * (!boardFlipped) + (7 - boardY) * (boardFlipped);

	clearAvailableMoves();

	switch (tchs[boardX + 8*boardY]) {

		case 'p':

			// one-step move

			if (getPieceType(tchs[getPos64(boardX, boardY + 1)]) == PIECE_BLANK) {

				availableMoves[getPos64(boardX, boardY + 1)] = 1;

				// two-step move

				if (boardY == 1)
					if (getPieceType(tchs[getPos64(boardX, boardY + 2)]) == PIECE_BLANK)
						availableMoves[getPos64(boardX, boardY + 2)] = 1;

			}

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
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
			}

			// down
			for (int i = getPos64(boardX, boardY + 1); i <= 64; i += 8) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
			}

			// left
			for (int i = getPos64(boardX - 1, boardY); i >= getPos64(0, boardY); i -= 1) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
			}

			// right
			for (int i = getPos64(boardX + 1, boardY); i <= getPos64(7, boardY); i += 1) {
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
			}

			break;

		case 'k':

			if (boardX > 0) {
				if (boardY > 0)
					if (getPieceType(tchs[getPos64(boardX - 1, boardY - 1)]) != PIECE_BLACK)
						availableMoves[getPos64(boardX - 1, boardY - 1)] = 1;
				if (boardY < 7)
					if (getPieceType(tchs[getPos64(boardX - 1, boardY + 1)]) != PIECE_BLACK)
						availableMoves[getPos64(boardX - 1, boardY + 1)] = 1;
			}

			if (boardX < 7) {
				if (boardY > 0)
					if (getPieceType(tchs[getPos64(boardX + 1, boardY - 1)]) != PIECE_BLACK)
						availableMoves[getPos64(boardX + 1, boardY - 1)] = 1;
				if (boardY < 7)
					if (getPieceType(tchs[getPos64(boardX + 1, boardY + 1)]) != PIECE_BLACK)
						availableMoves[getPos64(boardX + 1, boardY + 1)] = 1;
			}

			if (boardX > 0)
				if (getPieceType(tchs[getPos64(boardX - 1, boardY)]) != PIECE_BLACK)
					availableMoves[getPos64(boardX - 1, boardY)] = 1;

			if (boardX < 7)
				if (getPieceType(tchs[getPos64(boardX + 1, boardY)]) != PIECE_BLACK)
					availableMoves[getPos64(boardX + 1, boardY)] = 1;

			if (boardY > 0)
				if (getPieceType(tchs[getPos64(boardX, boardY - 1)]) != PIECE_BLACK)
					availableMoves[getPos64(boardX, boardY - 1)] = 1;

			if (boardY < 7)
				if (getPieceType(tchs[getPos64(boardX, boardY + 1)]) != PIECE_BLACK)
					availableMoves[getPos64(boardX, boardY + 1)] = 1;

			break;

		case 'q':
			break;

		case 'P':

			// one-step move

			if (getPieceType(tchs[getPos64(boardX, boardY - 1)]) == PIECE_BLANK) {

				availableMoves[getPos64(boardX, boardY - 1)] = 1;

				// two-step move

				if (
					(getPieceType(tchs[getPos64(boardX, boardY - 2)]) == PIECE_BLANK) &&
					(boardY == 6)
					)
				availableMoves[getPos64(boardX, boardY - 2)] = 1;

			}

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
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
			}

			// down
			for (int i = getPos64(boardX, boardY + 1); i <= 64; i += 8) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
			}

			// left
			for (int i = getPos64(boardX - 1, boardY); i >= getPos64(0, boardY); i -= 1) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
			}

			// right
			for (int i = getPos64(boardX + 1, boardY); i <= getPos64(7, boardY); i += 1) {
				if ( getPieceType(tchs[i]) == PIECE_WHITE ) break;
				availableMoves[i] = 1;
				if ( getPieceType(tchs[i]) == PIECE_BLACK ) break;
			}

			break;

		case 'K':

			if (boardX > 0) {
				if (boardY > 0)
					if (getPieceType(tchs[getPos64(boardX - 1, boardY - 1)]) != PIECE_WHITE)
						availableMoves[getPos64(boardX - 1, boardY - 1)] = 1;
				if (boardY < 7)
					if (getPieceType(tchs[getPos64(boardX - 1, boardY + 1)]) != PIECE_WHITE)
						availableMoves[getPos64(boardX - 1, boardY + 1)] = 1;
			}

			if (boardX < 7) {
				if (boardY > 0)
					if (getPieceType(tchs[getPos64(boardX + 1, boardY - 1)]) != PIECE_WHITE)
						availableMoves[getPos64(boardX + 1, boardY - 1)] = 1;
				if (boardY < 7)
					if (getPieceType(tchs[getPos64(boardX + 1, boardY + 1)]) != PIECE_WHITE)
						availableMoves[getPos64(boardX + 1, boardY + 1)] = 1;
			}

			if (boardX > 0)
				if (getPieceType(tchs[getPos64(boardX - 1, boardY)]) != PIECE_WHITE)
					availableMoves[getPos64(boardX - 1, boardY)] = 1;

			if (boardX < 7)
				if (getPieceType(tchs[getPos64(boardX + 1, boardY)]) != PIECE_WHITE)
					availableMoves[getPos64(boardX + 1, boardY)] = 1;

			if (boardY > 0)
				if (getPieceType(tchs[getPos64(boardX, boardY - 1)]) != PIECE_WHITE)
					availableMoves[getPos64(boardX, boardY - 1)] = 1;

			if (boardY < 7)
				if (getPieceType(tchs[getPos64(boardX, boardY + 1)]) != PIECE_WHITE)
					availableMoves[getPos64(boardX, boardY + 1)] = 1;


			break;

		case 'Q':
			break;

		default:
			break;

	}

};

