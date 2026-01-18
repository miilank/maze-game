/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for displaying mazes
*/

#pragma once
#include<iostream>
#include"Game.h"

class MatrixRenderer
{
	public:
	// display functions
	static void displayMatrix(Matrix& matrix, bool useColor, std::ostream& os = std::cout);
	static void display3x3Matrix(Matrix& matrix, bool useColor, Game& game, std::ostream& os = std::cout); // fog is activated
};