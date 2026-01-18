/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for implementation of special effect(hammer) that breaks down walls
*/

#pragma once
#include "Item.h"
class Matrix;
class Game;

class Hammer : public Item
{
	public:
	Hammer(int r, int c);
	void activate(Matrix& matrix, Game& game) override;
};