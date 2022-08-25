/******************************************************************************
 * game.hpp
 *
 * This file is the header file for the game.cpp module. It contains includes
 * and using namespace statements the class definition and int game(int argc,
 * char *argv[]) definition.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 10/15/2013
 * Modifications: 11/13/2014 Created the game.hpp module.
 *                11/16/2014 Added Board class and game(int argc, char
 *                           	*argv[]) function definitions.
 *                11/17/2014 Added taken pieces data structure
 *
******************************************************************************/

#ifndef GAME_HPP_
	#define GAME_HPP_
	#include <iostream>
	#include <string>
	#include <ctype.h>

	using namespace std;

	/******************************************************************************
	 *
	 * Class definitions
	 *
	 ******************************************************************************/

	class Board
	{
	public:
		string square[3][8][8];
		void populateBoard(void);
		void printBoardWhite(void);
		void printBoardBlack(void);
		int findPiecePositionLevel(string piece);
		int findPiecePositionRow(string piece);
		int findPiecePositionColumn(string piece);
		bool validateMove(string piece, int finalLevel, int finalRow,
				int finalColumn);
		void movePiece(string piece, int finalLevel, int finalRow,
				int finalColumn);
	};

	struct TakenPiece
	{
		string player;
		bool outOfPlay;
	};

	class TakenPieces
	{
	public:
		struct TakenPiece Piece[16];
		void populateList(string color);
		void removePiece(string deadPiece);
		void listPieces(void);
	};

	/******************************************************************************
	 *
	 * Function definitions
	 *
	 ******************************************************************************/

	int game(int argc, char *argv[]);

#endif /* GAME_HPP_ */
