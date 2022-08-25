/******************************************************************************
 * game.cpp
 *
 * This file runs the main Chess^3 game engine. It creates and populates the
 * board, prompts for moves from the players, and validates and places the
 * moves. It prints the board on command and resigns on command.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 10/15/2013
 * Modifications: 11/13/2014 Added call to game.cpp module.
 *                11/16/2014 Added functionality to populate the board and
 *                           	to move players' pieces.
 *                11/17/2014 Added functionality to print the board.
 *                           Changed printing of White and Black's sides and
 *                           	added level, rank, and file labels.
 *                           Converted moves to all upper case.
 *                           Added data structure with taken pieces, populated
 *                           	it, and programmed it to update when a piece
 *                           	is taken
 *
******************************************************************************/

/******************************************************************************
 *
 * Header inclusions
 *
******************************************************************************/

#include <iostream>
#include <string>
#include <ctype.h>
#include "game.hpp"

/******************************************************************************
 *
 * Namespaces
 *
******************************************************************************/

using namespace std;

/******************************************************************************
 * int game(int argc, char *argv[])
 *
 * This is the game function. It creates and populates the board, prompts for
 * moves from the players, and validates and places the moves.  It prints the
 * board on command and resigns on command.
 *
******************************************************************************/

int game(int argc, char *argv[])
{
	Board theBoard;
	int moveNumber = 0;
	string piece, tempPiece;
	bool gameOver = false;
	int finalLevel, finalRow, finalColumn;
	char finalColumnText;
	unsigned int count;
	bool validMove;
	TakenPieces WhitesPieces;
	TakenPieces BlacksPieces;

	theBoard.populateBoard();

	WhitesPieces.populateList("W");
	BlacksPieces.populateList("B");

	while(!(gameOver))
	{
		moveNumber++;
		validMove = false;

		while(!(validMove))
		{
			cout << "Enter White's move number " << moveNumber << endl;
			cout << "Piece to move ";

			cin >> piece;

			//Convert input to all upper case
			for(count = 0; count < piece.length(); count++)
			{
				piece[count] = toupper(piece[count]);
			}

			//Check to see if player resigned
			if(piece == "RRRR")
			{
				gameOver = true;
				validMove = true;
			}

			//Check to see if player wants the board printed
			else if(piece == "PPPP")
			{
				theBoard.printBoardWhite();
			}

			//Check to see if player wants a list of taken pieces listed
			else if(piece == "WLLL")
			{
				WhitesPieces.listPieces();
			}
			else if (piece == "BLLL")
			{
				BlacksPieces.listPieces();
			}
			else
			{
				cout << endl << "Board level to which to move the piece ";

				cin >> finalLevel;

				cout << endl << "Board file to which to move the piece ";

				cin >> finalColumnText;

				cout << endl << "Board rank to which to move the piece ";

				cin >> finalRow;

				//Massage data entry to machine-readable form
				finalLevel = finalLevel - 1;

				finalColumnText = toupper(finalColumnText);

				switch (finalColumnText)
				{
				case 'A':
					finalColumn = 0;
					break;
				case 'B':
					finalColumn = 1;
					break;
				case 'C':
					finalColumn = 2;
					break;
				case 'D':
					finalColumn = 3;
					break;
				case 'E':
					finalColumn = 4;
					break;
				case 'F':
					finalColumn = 5;
					break;
				case 'G':
					finalColumn = 6;
					break;
				case 'H':
					finalColumn = 7;
					break;
				}

				finalRow = finalRow - 1;

				validMove = theBoard.validateMove(piece, finalLevel, finalRow, finalColumn);

				if(validMove)
				{
					// If a piece was taken, populate the taken pieces data structure with that piece
					if(!(theBoard.square[finalLevel][finalRow][finalColumn] == "EEEE"))
					{
						tempPiece = theBoard.square[finalLevel][finalRow][finalColumn];
						BlacksPieces.removePiece(tempPiece);
					}
					theBoard.movePiece(piece, finalLevel, finalRow, finalColumn);
				}
				else
				{
					cout << "Invalid move!" << endl;
				}
			}
		}

		if(!gameOver)
		{
			validMove = false;

			while(!(validMove))
			{
				cout << "Enter Black's's move number " << moveNumber << endl;
				cout << "Piece to move: ";

				cin >> piece;

				//Convert input to all upper case
				for(count = 0; count < piece.length(); count++)
				{
					piece[count] = toupper(piece[count]);
				}

				//Check to see if player resigned
				if(piece == "RRRR")
				{
					gameOver = true;
					validMove = true;
				}

				//Check to see if player wants board printed
				else if(piece == "PPPP")
				{
					theBoard.printBoardBlack();
				}

				//Check to see if player wants a list of taken pieces listed
				else if(piece == "WLLL")
				{
					WhitesPieces.listPieces();
				}
				else if (piece == "BLLL")
				{
					BlacksPieces.listPieces();
				}
				else
				{
					cout << endl << "Board level to which to move the piece ";

					cin >> finalLevel;

					cout << endl << "Board file to which to move the piece ";

					cin >> finalColumnText;

					cout << endl << "Board rank to which to move the piece ";

					cin >> finalRow;

					//Massage the data entry to machine-readable form
					finalLevel = finalLevel - 1;

					finalColumnText = toupper(finalColumnText);

					switch (finalColumnText)
					{
					case 'A':
						finalColumn = 0;
						break;
					case 'B':
						finalColumn = 1;
						break;
					case 'C':
						finalColumn = 2;
						break;
					case 'D':
						finalColumn = 3;
						break;
					case 'E':
						finalColumn = 4;
						break;
					case 'F':
						finalColumn = 5;
						break;
					case 'G':
						finalColumn = 6;
						break;
					case 'H':
						finalColumn = 7;
						break;
					}

					finalRow = finalRow - 1;

					validMove = theBoard.validateMove(piece, finalLevel, finalRow, finalColumn);

					if(validMove)
					{
						// If a piece was taken, populate the taken pieces data structure with that piece
						if(!(theBoard.square[finalLevel][finalRow][finalColumn] == "EEEE"))
						{
							tempPiece = theBoard.square[finalLevel][finalRow][finalColumn];
							WhitesPieces.removePiece(tempPiece);
						}

						//Move the piece
						theBoard.movePiece(piece, finalLevel, finalRow, finalColumn);
					}
					else
					{
						cout << "Invalid move!" << endl;
					}
				}
			}
		}
	}
	cout << "Game over; thank you for playing" << endl;
	cout << "Have a day" << endl << endl;

	return 0;
 }

void Board::populateBoard(void)
{
	int i, j, k;

	i = 2;
	j = 0;
	Board::square[i][j][7] = "WKRE";
	Board::square[i][j][6] = "WKNE";
	Board::square[i][j][5] = "WKBE";
	Board::square[i][j][4] = "WKKE";
	Board::square[i][j][3] = "WQQE";
	Board::square[i][j][2] = "WQBE";
	Board::square[i][j][1] = "WQNE";
	Board::square[i][j][0] = "WQRE";

	j = 1;
	Board::square[i][j][7] = "WKRP";
	Board::square[i][j][6] = "WKNP";
	Board::square[i][j][5] = "WKBP";
	Board::square[i][j][4] = "WKKP";
	Board::square[i][j][3] = "WQQP";
	Board::square[i][j][2] = "WQBP";
	Board::square[i][j][1] = "WQNP";
	Board::square[i][j][0] = "WQRP";

	for(j = 2; j < 8; j++)
	{
		for(k = 0; k < 8; k++)
		{
			Board::square[i][j][k] = "EEEE";
		}
	}

	i = 1;
	for(j = 0; j < 8; j++)
	{
		for(k = 0; k < 8; k++)
		{
			Board::square[i][j][k] = "EEEE";
		}
	}

	i = 0;
	for(j = 0; j < 6; j++)
	{
		for(k = 0; k < 8; k++)
		{
			Board::square[i][j][k] = "EEEE";
		}
	}

	j = 6;
	Board::square[i][j][7] = "BKRP";
	Board::square[i][j][6] = "BKNP";
	Board::square[i][j][5] = "BKBP";
	Board::square[i][j][4] = "BKKP";
	Board::square[i][j][3] = "BQQP";
	Board::square[i][j][2] = "BQBP";
	Board::square[i][j][1] = "BQNP";
	Board::square[i][j][0] = "BQRP";

	j = 7;
	Board::square[i][j][7] = "BKRE";
	Board::square[i][j][6] = "BKNE";
	Board::square[i][j][5] = "BKBE";
	Board::square[i][j][4] = "BKKE";
	Board::square[i][j][3] = "BQQE";
	Board::square[i][j][2] = "BQBE";
	Board::square[i][j][1] = "BQNE";
	Board::square[i][j][0] = "BQRE";
}

void Board::printBoardWhite(void)
{
	int i, j, k;

	cout << endl;
	for(i = 2; i > -1; i--)
	{
		cout << "                   " << i+1 << endl;

		for(j = 7; j > -1; j--)
		{
			cout << j+1 << " ";

			for(k = 0; k < 8; k++)
			{
				cout << Board::square[i][j][k] << " ";
			}

			cout << endl;
		}

		cout << "   A    B    C    D    E    F    G    H  ";
		cout << endl << endl;
	}
}

void Board::printBoardBlack(void)
{
	int i, j, k;

	cout << endl;
	for(i = 2; i > -1; i--)
	{
		cout << "                   " << i+1 << endl;

		for(j = 0; j < 8; j++)
		{
			cout << j+1 << " ";

			for(k = 7; k > -1; k--)
			{
				cout << Board::square[i][j][k] << " ";
			}

			cout << endl;
		}

		cout << "   H    G    F    E    D    C    B    A  ";
		cout << endl << endl;
	}
}

int Board::findPiecePositionLevel(string piece)
{
	int i,j,k, ifound;

	ifound = -1;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 8; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(Board::square[i][j][k] == piece)
				{
					ifound = i;
				}
			}
		}
	}

	return ifound;
}

int Board::findPiecePositionRow(string piece)
{
	int i,j,k, jfound;

	jfound = -1;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 8; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(Board::square[i][j][k] == piece)
				{
					jfound = j;
				}
			}
		}
	}

	return jfound;
}

int Board::findPiecePositionColumn(string piece)
{
	int i,j,k, kfound;

	kfound = -1;

	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 8; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(Board::square[i][j][k] == piece)
				{
					kfound = k;
				}
			}
		}
	}

	return kfound;
}

bool Board::validateMove(string piece, int finalLevel, int finalRow,
		int finalColumn)
{
	int initialLevel, initialRow, initialColumn;
	bool validMove = false;
	char color, oppositeColor;
	Board possibleMoves;
	int i, j, k;
	bool blocked;


	// Locate the piece
	initialLevel = Board::findPiecePositionLevel(piece);
	initialRow = Board::findPiecePositionRow(piece);
	initialColumn = Board::findPiecePositionColumn(piece);

	if((initialLevel == -1) || (initialRow == -1) || (initialColumn == -1))
	{
		validMove = false;
		cout << "Unable to locate piece on the board!";
		return validMove;
	}
	else
	{
		//Populate the possible moves board
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 8; j++)
			{
				for(k = 0; k < 8; k++)
				{
					possibleMoves.square[i][j][k] = "NNNN";
				}
			}
		}
		//Determine the player's color
		color = piece[0];

		//Determine opposite color
		if(color == 'W')
		{
			oppositeColor = 'B';
		}
		else
		{
			oppositeColor = 'W';
		}

		//Make sure the move is legal

		//Man is a pawn
		if(piece[3] == 'P')
		{
			//Check for legal move for white player - this is the only man for which moves aren't white/black symmetric
			if(piece[0] == 'W')
			{
				//Moves without taking
				//See if player can move pawn up a level
				if(initialLevel + 1 < 3)
				{
					if(Board::square[initialLevel+1][initialRow][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel+1][initialRow][initialColumn] = "YYYY";
					}
				}

				//See if player can move pawn down a level
				if(initialLevel - 1 > -1)
				{
					if(Board::square[initialLevel-1][initialRow][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel-1][initialRow][initialColumn] = "YYYY";
					}
				}

				//See if player can move pawn forward
				if(initialRow + 1 < 8)
				{
					if(Board::square[initialLevel][initialRow+1][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel][initialRow+1][initialColumn] = "YYYY";
					}
				}

				//Moves with taking
				//Take same level to right
				if((initialRow + 1 < 8)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel][initialRow+1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel][initialRow+1][initialColumn+1] = "YYYY";
					}
				}
				//Take same level to left
				if((initialRow + 1 < 8)&&(initialColumn - 1 < -1))
				{
					if(Board::square[initialLevel][initialRow+1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel][initialRow+1][initialColumn-1] = "YYYY";
					}
				}

				//Take 1 level up to right
				if((initialLevel + 1 < 3)&&(initialRow + 1 < 8)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel+1][initialRow+1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel+1][initialRow+1][initialColumn+1] = "YYYY";
					}
				}
				//Take 1 level up to left
				if((initialLevel + 1 > 3)&&(initialRow + 1 < 8)&&(initialColumn -1 > -1))
				{
					if(Board::square[initialLevel+1][initialRow+1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel+1][initialRow+1][initialColumn-1] = "YYYY";
					}
				}

				//Take 1 level down to right
				if((initialLevel - 1 > -1)&&(initialRow + 1 < 8)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel-1][initialRow+1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel-1][initialRow+1][initialColumn+1] = "YYYY";
					}
				}
				//Take 1 level down to left
				if((initialLevel - 1 > -1)&&(initialRow + 1 < 8)&&(initialColumn - 1 > -1))
				{
					if(Board::square[initialLevel-1][initialRow+1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel-1][initialRow+1][initialColumn-1] = "YYYY";
					}
				}
			}

			//Check for legal move for black player
			else
			{
				//Moves without taking
				//See if player can move pawn up a level
				if(initialLevel + 1 < 3)
				{
					if(Board::square[initialLevel+1][initialRow][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel+1][initialRow][initialColumn] = "YYYY";
					}
				}

				//See if player can move pawn down a level
				if(initialLevel - 1 > -1)
				{
					if(Board::square[initialLevel-1][initialRow][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel-1][initialRow][initialColumn] = "YYYY";
					}
				}

				//See if player can move pawn forward
				if(initialRow - 1 > -1)
				{
					if(Board::square[initialLevel][initialRow-1][initialColumn] == "EEEE")
					{
						possibleMoves.square[initialLevel][initialRow-1][initialColumn] = "YYYY";
					}
				}

				//Moves with taking
				//Take same level to right
				if((initialRow - 1 > -1)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel][initialRow-1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel][initialRow-1][initialColumn+1] = "YYYY";
					}
				}
				//Take same level to left
				if((initialRow - 1 > -1)&&(initialColumn - 1 < -1))
				{
					if(Board::square[initialLevel][initialRow-1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel][initialRow-1][initialColumn-1] = "YYYY";
					}
				}

				//Take 1 level up to right
				if((initialLevel + 1 < 3)&&(initialRow - 1 > -1)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel+1][initialRow-1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel+1][initialRow-1][initialColumn+1] = "YYYY";
					}
				}
				//Take 1 level up to left
				if((initialLevel + 1 > 3)&&(initialRow - 1 > -1)&&(initialColumn - 1 > -1))
				{
					if(Board::square[initialLevel+1][initialRow-1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel+1][initialRow-1][initialColumn-1] = "YYYY";
					}
				}

				//Take 1 level down to right
				if((initialLevel - 1 > -1)&&(initialRow - 1 > -1)&&(initialColumn + 1 < 8))
				{
					if(Board::square[initialLevel-1][initialRow-1][initialColumn+1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel-1][initialRow-1][initialColumn+1] = "YYYY";
					}
				}
				//Take 1 level down to left
				if((initialLevel - 1 > -1)&&(initialRow - 1 > -1)&&(initialColumn -1 > -1))
				{
					if(Board::square[initialLevel-1][initialRow-1][initialColumn-1][0] == oppositeColor)
					{
						possibleMoves.square[initialLevel-1][initialRow-1][initialColumn-1] = "YYYY";
					}
				}
			}

			//See if final square is allowable for this man
			if(possibleMoves.square[finalLevel][finalRow][finalColumn] == "YYYY")
			{
				validMove = true;
			}
			else
			{
				validMove = false;
			}
		}

		//Must be dealing with a piece
		else
		{
			switch(piece[2])
			{
				//Piece is the king
				case 'K':
				{
					//Loop though the solid cube of squares surrounding the king
					for(i = -1; i < 2; i++)
					{
						for(j = -1; j < 2; j++)
						{
							for(k = -1; k < 2; k++)
							{
								//Make sure we're still in-bounds
								if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
								{
									//If there isn't a man of the opposite color, we can legally move there
									if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
									{
										possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
									}
								}
							}
						}
					}

					//See if final square is allowable for this man
					if(possibleMoves.square[finalLevel][finalRow][finalColumn] == "YYYY")
					{
						validMove = true;
					}
					else
					{
						validMove = false;
					}
				}
				//Piece is a knight
				case 'N':
				{
					//2 steps in vertical direction, 1 step forward/backwards or left/right
					for(i = -2; i < 3; i += 4)
					{
						//1 step forwards/backwards
						for(j = -1; j < 2; j += 2)
						{
							k = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
						//1 step left/right
						for(k = -1; k < 2; k += 2)
						{
							j = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
					}
					//2 steps forwards/backwards, 1 step vertically for left/right
					for(j = -2; j < 3; j += 4)
					{
						//1 step vertically
						for(i = -1; i < 2; i += 2)
						{
							k = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
						//1 step forwards/backwards
						for(k = -1; k < 2; k += 2)
						{
							i = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
					}
					//2 steps left/right
					for(k = -2; k < 3; k += 4)
					{
						//1 step vertically
						for(i = -1; i < 2; i += 2)
						{
							j = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
						//1 step forwards/backwards
						for(j = -1; j < 2; j += 2)
						{
							i = 0;
							//Make sure we're still in-bounds
							if((initialLevel + i > -1)&&(initialLevel + i < 3)&&(initialRow + j > -1)&&(initialRow + j < 8)&&(initialColumn + k > -1)&&(initialColumn + k < 8))
							{
								//If there isn't a man of the opposite color, we can legally move there
								if(Board::square[initialLevel+i][initialRow+j][initialColumn+k][0] != color)
								{
									possibleMoves.square[initialLevel+i][initialRow+j][initialColumn+k] = "YYYY";
								}
							}
						}
					}

					//See if final square is allowable for this man
					if(possibleMoves.square[finalLevel][finalRow][finalColumn] == "YYYY")
					{
						validMove = true;
					}
					else
					{
						validMove = false;
					}
				}
				//Piece is a rook
				case 'R':
				{
					//Check squares above
					blocked = false;
					i = 0;
					while((!(blocked))&&(i < 3))
					{
						i++;
						if(initialLevel + i < 3)
						{
							if(Board::square[initialLevel+i][initialRow][initialColumn][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel+i][initialRow][initialColumn][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel+i][initialRow][initialColumn] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel+i][initialRow][initialColumn] = "YYYY";
							}
						}
					}

					//Check squares below
					blocked = false;
					i = 0;
					while((!(blocked))&&(i > -3))
					{
						i--;
						if(initialLevel + i > -1)
						{
							if(Board::square[initialLevel+i][initialRow][initialColumn][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel+i][initialRow][initialColumn][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel+i][initialRow][initialColumn] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel+i][initialRow][initialColumn] = "YYYY";
							}
						}
					}

					//Check squares to the right
					blocked = false;
					j = 0;
					while((!(blocked))&&(j < 8))
					{
						j++;
						if(initialRow + j < 8)
						{
							if(Board::square[initialLevel][initialRow+j][initialColumn][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel][initialRow+j][initialColumn][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel][initialRow+j][initialColumn] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel][initialRow+j][initialColumn] = "YYYY";
							}
						}
					}

					//Check squares to the left
					blocked = false;
					j = 0;
					while((!(blocked))&&(j > -8))
					{
						j--;
						if(initialRow + j > -1)
						{
							if(Board::square[initialLevel][initialRow+j][initialColumn][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel][initialRow+j][initialColumn][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel][initialRow+j][initialColumn] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel][initialRow+j][initialColumn] = "YYYY";
							}
						}
					}

					//Check squares in front
					blocked = false;
					k = 0;
					while((!(blocked))&&(k < 8))
					{
						k++;
						if(initialColumn + k < 8)
						{
							if(Board::square[initialLevel][initialRow][initialColumn+k][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel][initialRow][initialColumn+k][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel][initialRow][initialColumn+k] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel][initialRow][initialColumn+k] = "YYYY";
							}
						}
					}

					//Check squares in back
					blocked = false;
					k = 0;
					while((!(blocked))&&(k > -8))
					{
						k--;
						if(initialColumn + k > -1)
						{
							if(Board::square[initialLevel][initialRow][initialColumn+k][0] == color)
							{
								blocked = true;
							}
							else if(Board::square[initialLevel][initialRow][initialColumn+k][0] == oppositeColor)
							{
								blocked = true;
								possibleMoves.square[initialLevel][initialRow][initialColumn+k] = "YYYY";
							}
							else
							{
								possibleMoves.square[initialLevel][initialRow][initialColumn+k] = "YYYY";
							}
						}
					}

					//See if final square is allowable for this man
					if(possibleMoves.square[finalLevel][finalRow][finalColumn] == "YYYY")
					{
						validMove = true;
					}
					else
					{
						validMove = false;
					}
				}
				case 'B': //Piece is a bishop
				{

				}
				case 'Q': //Piece is a queen
				{

				}
			}
		}
	}

	// Validate the move for each piece

	return validMove;
}

void Board::movePiece(string piece, int finalLevel, int finalRow,
		int finalColumn)
{
	int initialLevel, initialRow, initialColumn;

	initialLevel = Board::findPiecePositionLevel(piece);
	initialRow = Board::findPiecePositionRow(piece);
	initialColumn = Board::findPiecePositionColumn(piece);

	Board::square[finalLevel][finalRow][finalColumn] = piece;
	Board::square[initialLevel][initialRow][initialColumn] = "EEEE";
}

void TakenPieces::populateList(string color)
{
	int i;

	TakenPieces::Piece[0].player = color + "KRE";
	TakenPieces::Piece[1].player = color + "KNE";
	TakenPieces::Piece[2].player = color + "KBE";
	TakenPieces::Piece[3].player = color + "KKE";
	TakenPieces::Piece[4].player = color + "QQE";
	TakenPieces::Piece[5].player = color + "QBE";
	TakenPieces::Piece[6].player = color + "QNE";
	TakenPieces::Piece[7].player = color + "QRE";
	TakenPieces::Piece[8].player = color + "KRP";
	TakenPieces::Piece[9].player = color + "KNP";
	TakenPieces::Piece[10].player = color + "KBP";
	TakenPieces::Piece[11].player = color + "KKP";
	TakenPieces::Piece[12].player = color + "QQP";
	TakenPieces::Piece[13].player = color + "QBP";
	TakenPieces::Piece[14].player = color + "QNP";
	TakenPieces::Piece[15].player = color + "QRP";

	for(i = 0; i < 16; i++)
	{
		TakenPieces::Piece[i].outOfPlay = false;
	}
}

void TakenPieces::removePiece(string deadPiece)
{
	int i;

	for(i = 0; i < 16; i++)
	{
		if(TakenPieces::Piece[i].player == deadPiece)
		{
			TakenPieces::Piece[i].outOfPlay = true;
		}
	}
}

void TakenPieces::listPieces(void)
{
	int i;

	for(i = 0; i < 16; i++)
	{
		if(TakenPieces::Piece[i].outOfPlay == true)
		{
			cout << TakenPieces::Piece[i].player << endl;
		}

	}
}
