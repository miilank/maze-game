/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for implementation of special effect(fog) that reduces the visibility of the matrix to a 3x3 submatrix
*/

#pragma once
#include "Item.h"
class Matrix;
class Game;

class Fog : public Item
{
	public:
	Fog(int r, int c);
	void activate(Matrix& matrix, Game& game) override;
};