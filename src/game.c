
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 *
 * getPos64            -> Convert the X and Y into a single number from 0 to 63
 *
 * clearAvailableMoves -> Self-explanatory
 *
 * getPieceType        -> Return true/false based on if the piece type matches the specified
 * checkSpotType       -> Check that the sport on (spotX, spotY) is free for the piece to step on
 * gameGetMoves        -> Get all avalable moves for a piece on (boardX, boardY) and store them in availableMoves
 */

#include <stdio.h>

#include "./include/game.h"
#include "./include/tchs.h"

#define getPos64(x, y) (x + 8*(y))

extern int  boardFlipped; // -> win.c
extern char tchs[64];     // -> tchs.c

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

int kMoves[8][2] = {
	{ 0,  1}, { 0, -1}, { 1,  0}, { 1,  1},
	{ 1, -1}, {-1,  0}, {-1,  1}, {-1, -1}
};

int nMoves[8][2] = {
	{ 1,  2}, { 1, -2}, { 2,  1}, { 2, -1},
	{-1,  2}, {-1, -2}, {-2,  1}, {-2, -1}
};

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

int checkSpotType(int pieceX, int pieceY, int pieceType) {

	if ((pieceX < 0) || (pieceX > 7) || (pieceY < 0) || (pieceY > 7)) return 0;

	return (getPieceType(tchs[getPos64(pieceX, pieceY)]) == pieceType);

}

void clearAvailableMoves() { for (unsigned int i = 0; i < 64; i++) availableMoves[i] = 0; }

// TODO: King movement rework
// TODO: Bishop, queen

int spotX, spotY;
int bishopTmp;
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

			// up-left

			// up-right

			// down-left

			// down-right

			break;

		case 'n':

			for (int i = 0; i < 8; i++) {
				spotX = boardX + nMoves[i][0];
				spotY = boardY + nMoves[i][1];
				if (
						checkSpotType(spotX, spotY, PIECE_WHITE) ||
						checkSpotType(spotX, spotY, PIECE_BLANK)
						)
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

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

			for (unsigned int i = 0; i < 8; i++) {
				spotX = boardX + kMoves[i][0];
				spotY = boardY + kMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, PIECE_WHITE)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
					)
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		case 'q':
			break;

		case 'P':

			// one-step move

			if (getPieceType(tchs[getPos64(boardX, boardY - 1)]) == PIECE_BLANK) {

				availableMoves[getPos64(boardX, boardY - 1)] = 1;

				// two-step move

				if (boardY == 6)
					if (getPieceType(tchs[getPos64(boardX, boardY - 2)]) == PIECE_BLANK)
						availableMoves[getPos64(boardX, boardY - 2)] = 1;

			}

			break;

		case 'B':

			bishopTmp = 0;
			while (++bishopTmp) {

				spotX = boardX + bishopTmp;
				spotY = boardY + bishopTmp;

				if (checkSpotType(spotX, spotY, PIECE_BLACK)) {
					availableMoves[getPos64(spotX, spotY)] = 1;
					break;
				}
				else if (checkSpotType(spotX, spotY, PIECE_BLANK)) {
					availableMoves[getPos64(spotX, spotY)] = 1;
				}
				else break;

			}

			break;

		case 'N':

			for (int i = 0; i < 8; i++) {
				spotX = boardX + nMoves[i][0];
				spotY = boardY + nMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, PIECE_BLACK)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
				   )
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

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

			for (unsigned int i = 0; i < 8; i++) {
				spotX = boardX + kMoves[i][0];
				spotY = boardY + kMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, PIECE_BLACK)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
				   )
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		case 'Q':
			break;

		default:
			break;

	}

};

