/******************************************************************************
 * chesscubed.c
 *
 * This program plays a game of Chess^3/Strato Chess. It instantiates and
 * populates the board, and takes moves from the players.
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 10/15/2013
 * Modifications: None
 ******************************************************************************/

/******************************************************************************
 * main.cpp
 *
 * This file calls calls the major function, game(int argc, char *argv[])).
 *
 * Author:        Jeffrey Rolland
 * Creation Date: 10/15/2013
 * Modifications: 11/13/2014 Added call to game.cpp module.
 *                11/17/2014 Added program header statement and a returnValue
 *                           feature from game().
 *
******************************************************************************/

/******************************************************************************
 *
 * Header inclusions
 *
******************************************************************************/

#include "game.hpp"

/******************************************************************************
 * int main(int argc, char *argv[])
 *
 * This is the main function. It calls the game(int argc, char *argv[]))
 * function.
******************************************************************************/

int main(int argc, char *argv[])
 {
	int returnValue;

	returnValue = game(argc, argv);

	return returnValue;
 }
