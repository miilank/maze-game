/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: Item represents an abstract base class for the various types of items found in the game.
	Its main purpose is to define the basic attributes and functions that specific objects must implement.
	This class uses the polymorphism mechanism to allow different behavior of specific objects through the virtual function activate.
*/

#pragma once
class Matrix;
class Game;

class Item
{
	protected:
	int row, col;
	char type;
	public:
	Item(int r, int c, char t);
	virtual void activate(Matrix& matrix, Game& game) = 0;

	// getters
	int getRow();
	int getCol();
	char getType();
};