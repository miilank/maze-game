/*
Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: A class for generating a cell, as the basic element of a matrix (maze).
*/

#pragma once

class Cell
{
private:
	char type;

public:
	Cell();
	void setType(char newType);
	char getType() const;
};
