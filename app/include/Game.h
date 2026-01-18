/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class that contains game control, robot and minotaur movement functions.
*/

#pragma once
#include "Matrix.h"
#include<fstream>
#include<sstream>
#include<string>
#include"MatrixRenderer.h"

class Game
{
private:
	int robotRow, robotCol;
	int robotNewRow, robotNewCol;
	int minotaurRow, minotaurCol;
	int itemDuration;
public:
	bool isFog;
	bool hasSword;
	bool minotaurKilled;
	bool hasShield;
	bool hasHammer;
	// constructor
	Game(int robotRow, int robotCol, int minotaurRow, int minotaurCol);

	// movements
	bool moveRobot(Matrix& matrix, char direction);
	bool moveMinotaur(Matrix& matrix);

	// helper functions
	bool isValidMove(Matrix& matrix, int newRow, int newCol);
	void handleParticularCells(Matrix& matrix, int newRow, int newCol); // check if WON and check which item should be activated
	void updatePosition(Matrix& matrix, int oldRow, int oldCol, int newRow, int newCol, char type); // update position of the Robot or the Minotaur
	void handleItemEffects(Matrix& matrix);	// activate the effect
	bool checkMinotaurEatsRobot(Matrix& matrix);
	void randomMinotaurMove(Matrix& matrix, int exitRow, int exitCol);
	int findItemIndex(Matrix& matrix, int row, int col) const;
	void playTheGame(Matrix& matrix);
	void displayControls();
	void displayMatrix(Matrix& matrix); // if fog is not activated(cleaner code)
	void handleInvalidMove(Matrix& matrix); // when the fog is(not) activated, handle the message(cleaner code)

	// getters and setters
	int getRobotRow();
	void setRobotRow(int row);
	int getRobotCol();
	void setRobotCol(int col);
	int getRobotNewRow();
	void setRobotNewRow(int row);
	int getRobotNewCol();
	void setRobotNewCol(int col);
	int getMinotaurRow();
	void setMinotaurRow(int row);
	int getMinotaurCol();
	void setMinotaurCol(int col);
	int getItemDuration();
	void setItemDuration(int itemDuration);
};