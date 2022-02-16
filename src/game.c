
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 */

#include <stdio.h>

#include "./include/game.h"
#include "./include/game_assist.h"
#include "./include/tchs.h"

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

// TODO: King movement rework
// TODO: Bishop, queen

int spotX, spotY;
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

			bishopCheckDiagonal(boardX, boardY,  1,  1, PIECE_WHITE);
			bishopCheckDiagonal(boardX, boardY,  1, -1, PIECE_WHITE);
			bishopCheckDiagonal(boardX, boardY, -1,  1, PIECE_WHITE);
			bishopCheckDiagonal(boardX, boardY, -1, -1, PIECE_WHITE);

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

			bishopCheckDiagonal(boardX, boardY,  1,  1, PIECE_BLACK);
			bishopCheckDiagonal(boardX, boardY,  1, -1, PIECE_BLACK);
			bishopCheckDiagonal(boardX, boardY, -1,  1, PIECE_BLACK);
			bishopCheckDiagonal(boardX, boardY, -1, -1, PIECE_BLACK);

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

