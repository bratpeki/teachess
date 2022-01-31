
/*
 * game.c - Handle game logic
 *
 * Header: game.h
 *
 * gameGetMoves -> Get all avalable moves for a piece on (boardX, boardY)
 */

#include <stdio.h>

#include "./include/tchs.h"

int gameTurn;

extern int boardFlipped; // -> win.c

void gameGetMoves(int boardX, int boardY) {

	switch (tchsGetPiece(boardX, boardY, boardFlipped)) {

		case 'p':
			printf("Black Pawn!\n");
			break;

		case 'b':
			printf("Black Bishop!\n");
			break;

		case 'n':
			printf("Black Knight!\n");
			break;

		case 'r':
			printf("Black Rook!\n");
			break;

		case 'k':
			printf("Black King!\n");
			break;

		case 'q':
			printf("Black Queen!\n");
			break;

		case 'P':
			printf("White Pawn!\n");
			break;

		case 'B':
			printf("White Bishop!\n");
			break;

		case 'N':
			printf("White Knight!\n");
			break;

		case 'R':
			printf("White Rook!\n");
			break;

		case 'K':
			printf("White King!\n");
			break;

		case 'Q':
			printf("White Queen!\n");
			break;

		default:
			printf("None!\n");
			break;

	}

};

