/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for generating mazes
*/

#pragma once
#include<iostream>
#include<queue>
#include<ctime>
#include<chrono>
#include<cmath>
#include"Cell.h"
#include"Item.h"
#include"Fog.h"
#include"Sword.h"
#include"Shield.h"
#include"Hammer.h"
#include"Game.h"
#include"FileManager.h"

class Matrix
{
	private:
	int rows;
	int cols;
	int noOfItems;
	Cell** matrix;
	std::vector<Item*> items;
	Item* currentItem;

	public:
	// constructor and destructor
	Matrix(int rows, int cols, int noOfItems, int moveCount);
	~Matrix();

	// maze generation functions
	void generateMaze(Game& game);
	void initializeMatrix();
	void setExteriorWalls();
	void setEntranceAndExit(Game& game);
	int calculateOptimalWalls();	// optimal number of inner walls
	int calculateOptimalNumOfItems();	// optimal(max) number of special effects
	int calculateMaxWalls(int rows, int cols);	// max number of inner walls
	bool generateInnerWalls(Game& game, int remainingWalls);
	bool hasPath(Game& game);	// check if there is clear path between entrance and exit
	int findExitColumn();
	bool** allocateVisitedMatrix(); // used in BFS algorithm
	void freeVisitedMatrix(bool** visited); // used in BFS algorithm
	bool bfsPathExists(int entranceRow, int entranceCol, int exitRow, int exitCol, bool** visited); // BFS algorithm
	bool isValidCell(int newRow, int newCol, bool** visited);
	void setItems(Game& game);
	void setMinotaurPosition(Game& game);
	void placeSpecialItems(Game& game);

	// getters and setters
	Cell** getMatrix();
	void setMatrix(Cell** matrix);
	int getMatrixRows();
	int getMatrixCols();
	int getNoOfItems();
	Item* getCurrentItem();
	void setCurrentItem(Item* item);
	std::vector<Item*>& getItems();
	void setItems(Item* item);
};