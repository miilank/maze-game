#include "FileManager.h"
#include<iostream>
#include<fstream>

void FileManager::writeToFile(const std::string& filename, const std::string& content) {
	if (std::ofstream file(filename); file.is_open()) {
		file << content;
		file.close();
	}
	else {
		std::cerr << "Error opening file." << std::endl;
	}
}
