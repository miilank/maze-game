/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for implementation of special effect(sword) that the robot uses to kill the minotaur
*/

#pragma once
#include "Item.h"
class Matrix;
class Game;

class Sword : public Item
{
	public:
	Sword(int r, int c);
	void activate(Matrix& matrix, Game& game) override;
};