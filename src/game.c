
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 */

#include <stdio.h>

#include "./include/game.h"
#include "./include/game_assist.h"
#include "./include/tchs.h"

extern char tchs[64];     // -> tchs.c
extern int  boardFlipped; // -> win.c
extern int  intTmp;       // -> tmp.c

int gameTurn;
int availableMoves[64];

int kMoves[8][2] = {
	{ 0,  1}, { 0, -1}, { 1,  0}, { 1,  1},
	{ 1, -1}, {-1,  0}, {-1,  1}, {-1, -1}
};

int nMoves[8][2] = {
	{ 1,  2}, { 1, -2}, { 2,  1}, { 2, -1},
	{-1,  2}, {-1, -2}, {-2,  1}, {-2, -1}
};

// TODO: Single cases instead of doubles

int spotX, spotY;

int pieceType;
int piecePos;

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

		case 'b':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType);

			break;

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

		case 'r':

			gameCheckLine(boardX, boardY,  0,  1, !pieceType);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType);

			break;

		case 'c':

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

		case 'q':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType);

			gameCheckLine(boardX, boardY,  0,  1, !pieceType);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType);

			break;

		case 'P':

			// one-step move

			if (getPieceType(tchs[piecePos - 8]) == PIECE_BLANK) {

				availableMoves[piecePos - 8] = 1;

				// two-step move

				if (boardY == 6)
					availableMoves[piecePos - 16] = (getPieceType(tchs[piecePos - 16]) == PIECE_BLANK);

			}

			availableMoves[piecePos - 7] = (getPieceType(tchs[piecePos - 7]) == !pieceType);
			availableMoves[piecePos - 9] = (getPieceType(tchs[piecePos - 9]) == !pieceType);

			break;

		case 'E':

			availableMoves[piecePos - 8] = (getPieceType(tchs[piecePos - 8]) == PIECE_BLANK);

			break;

		case 'B':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType);

			break;

		case 'N':

			for (int i = 0; i < 8; i++) {
				spotX = boardX + nMoves[i][0];
				spotY = boardY + nMoves[i][1];
				if (
						(checkSpotType(spotX, spotY, !pieceType)) ||
						(checkSpotType(spotX, spotY, PIECE_BLANK))
				   )
					availableMoves[getPos64(spotX, spotY)] = 1;
			}

			break;

		case 'R':

			gameCheckLine(boardX, boardY,  0,  1, !pieceType);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType);

			break;

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

		case 'Q':

			gameCheckLine(boardX, boardY,  1,  1, !pieceType);
			gameCheckLine(boardX, boardY,  1, -1, !pieceType);
			gameCheckLine(boardX, boardY, -1,  1, !pieceType);
			gameCheckLine(boardX, boardY, -1, -1, !pieceType);

			gameCheckLine(boardX, boardY,  0,  1, !pieceType);
			gameCheckLine(boardX, boardY,  0, -1, !pieceType);
			gameCheckLine(boardX, boardY,  1,  0, !pieceType);
			gameCheckLine(boardX, boardY, -1,  0, !pieceType);

			break;

		default:

			break;

	}

};

