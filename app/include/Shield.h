/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for implementation of special effect(shield) that the robot uses to protect itself from the minotaur
*/

#pragma once
#include "Item.h"
class Matrix;
class Game;

class Shield : public Item
{
	public:
	Shield(int r, int c);
	void activate(Matrix& matrix, Game& game) override;
};