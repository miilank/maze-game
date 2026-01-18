/*
	Author: Milan Kacarevic
	The Last Change: 30.1.2025.
	A Brief Description Of The Functionality: It is used to write the matrix to a file in case of game over.
*/

#pragma once
#include<string>
class FileManager
{
	public:
	static void writeToFile(const std::string& filename, const std::string& content);
};