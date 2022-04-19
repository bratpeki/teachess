
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 */

#include "include/game.h"
#include "include/game_assist.h"
#include "include/tchs.h"

#include <stdio.h>

extern char tchs[64];     // -> tchs.c
extern int  boardFlipped; // -> win.c

char boardOuterChars[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
char currentNotation[CHAR_COUNT_GAME_NOTATION];

int availableMoves[64];
int checkStopMoves[64];

int kMoves[8][2] = {
	{ 0,  1}, { 0, -1}, { 1,  0}, { 1,  1},
	{ 1, -1}, {-1,  0}, {-1,  1}, {-1, -1}
};

int nMoves[8][2] = {
	{ 1,  2}, { 1, -2}, { 2,  1}, { 2, -1},
	{-1,  2}, {-1, -2}, {-2,  1}, {-2, -1}
};

int gameTurn;
int piecePos;
int pieceType;
int spotX, spotY;

void gameGetMoves(int boardX, int boardY) {

	clearAvailableMoves();

	piecePos  = getPos64(boardX, boardY);
	pieceType = getPieceType(tchs[piecePos]);

	switch (tchs[piecePos]) {

		case 'p':

			if (getPieceType(tchs[piecePos + 8]) == PIECE_BLANK) {

				availableMoves[piecePos + 8] = 1;

				if (boardY == 1)
					availableMoves[piecePos + 16] = (getPieceType(tchs[piecePos + 16]) == PIECE_BLANK);

			}

			availableMoves[piecePos + 9] = (getPieceType(tchs[piecePos + 9]) == !pieceType);
			availableMoves[piecePos + 7] = (getPieceType(tchs[piecePos + 7]) == !pieceType);

			break;

		case 'e':

			availableMoves[piecePos + 8] = (getPieceType(tchs[piecePos + 8]) == PIECE_BLANK);

			break;

		case 'B':
		case 'b':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType, availableMoves);

			break;

		case 'N':
		case 'n':

			for (int i = 0; i < 8; i++) {
				spotX = boardX + nMoves[i][0];
				spotY = boardY + nMoves[i][1];
				if (
						checkSpotType(spotX, spotY, !pieceType) ||
						checkSpotType(spotX, spotY, PIECE_BLANK)
						)
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		case 'R':
		case 'r':

			gameCheckLine(boardX, boardY,  0,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType, availableMoves);

			break;

		case 'Q':
		case 'q':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType, availableMoves);

			gameCheckLine(boardX, boardY,  0,  1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType, availableMoves);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType, availableMoves);

			break;

		case 'P':

			if (getPieceType(tchs[piecePos - 8]) == PIECE_BLANK) {

				availableMoves[piecePos - 8] = 1;

				if (boardY == 6)
					availableMoves[piecePos - 16] = (getPieceType(tchs[piecePos - 16]) == PIECE_BLANK);

			}

			availableMoves[piecePos - 7] = (getPieceType(tchs[piecePos - 7]) == !pieceType);
			availableMoves[piecePos - 9] = (getPieceType(tchs[piecePos - 9]) == !pieceType);

			break;

		case 'E':

			availableMoves[piecePos - 8] = (getPieceType(tchs[piecePos - 8]) == PIECE_BLANK);

			break;

		case 'c':
		case 'C':

			for (unsigned int i = 0; i < 8; i++) {
				spotX = boardX + kMoves[i][0];
				spotY = boardY + kMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, !pieceType)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
					)
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		case 'k':
		case 'K':

			for (unsigned int i = 0; i < 8; i++) {
				spotX = boardX + kMoves[i][0];
				spotY = boardY + kMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, !pieceType)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
				   )
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		default: break;

	}

}

void gameGetNotation(int x1, int y1, int x2, int y2) {

	/* Clearing the content of the game notation */

	for (int i = 0; i < CHAR_COUNT_GAME_NOTATION - 1; i++) currentNotation[i] = ' ';

	// printf ("1. %d-%d\n2. %d-%d\n", x1, y1, x2, y2);

	if (
			(tchs[getPos64(x1, y1)] != 'p') &&
			(tchs[getPos64(x1, y1)] != 'P')
			)
		printf("%c", tchs[getPos64(x1, y1)]);

	printf("%c%d", boardOuterChars[x2], 8 - y2);

	printf("\n");

	printf("Ate: %d\n", (tchs[getPos64(x2, y2)] != '-') && (tchs[getPos64(x2, y2)] != '.'));

}

