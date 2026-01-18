/*
    Author: Milan Kacarevic
    The Last Change: 30.1.2025.
    A Brief Description Of The Functionality: This file contains the 'main' function. Program execution begins and ends there.
    It displays basic information about the program, runs and binds all blocks, and measures and displays the maze generation time.
    It checks if the input parameters are valid and calculates the column in which the robot will be placed, without it being an edge.
*/

#include <iostream>
#include <chrono>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <string>
#include <random>

#include "Matrix.h"
#include "Game.h"
#include "MatrixRenderer.h"

static void validateArgumentCount(const int argc) {
    if (argc != 4) {
        throw std::invalid_argument("Usage: <program> <rows> <cols> <numOfItems>");
    }
}

static void validateArgumentsAreIntegers(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (const auto ch = static_cast<unsigned char>(argv[i][j]); !std::isdigit(ch)) {
                throw std::invalid_argument("Error: All arguments must be integers.");
            }
        }
    }
}

static void validateValuesInRange(int rows, int cols, int numOfItems, int maxNumOfItems) {
    constexpr int minRows = 15;
    constexpr int minCols = 15;

    if (constexpr int maxRows = 1500; rows <= minRows || rows > maxRows) {
        std::ostringstream oss;
        oss << "Error: Number of rows must be in the range (" << minRows << " - " << maxRows << "].";
        throw std::out_of_range(oss.str());
    }

    if (constexpr int maxCols = 200; cols <= minCols || cols > maxCols) {
        std::ostringstream oss;
        oss << "Error: Number of columns must be in the range (" << minCols << " - " << maxCols << "].";
        throw std::out_of_range(oss.str());
    }

    if (constexpr int minItems = 3; numOfItems <= minItems || numOfItems >= maxNumOfItems) {
        std::ostringstream oss;
        oss << "Error: Number of items must be greater than " << minItems
            << " and less than " << maxNumOfItems
            << " (this depends on the entered matrix dimensions).";
        throw std::out_of_range(oss.str());
    }
}

int main(int argc, char* argv[]) {
    try {
        validateArgumentCount(argc);
        validateArgumentsAreIntegers(argc, argv);

        const int rows = std::stoi(argv[1]);
        const int cols = std::stoi(argv[2]);
        const int numOfItems = std::stoi(argv[3]);

        // Construct matrix first so we can compute maxNumOfItems based on dimensions
        Matrix matrix(rows, cols, numOfItems, 0);
        const int maxNumOfItems = matrix.calculateOptimalNumOfItems();

        validateValuesInRange(rows, cols, numOfItems, maxNumOfItems);

        // Random entrance column in range [1, cols-2] (never an edge)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, cols - 2);
        const int entranceCol = dist(gen);

        Game game(1, entranceCol, -1, -1);

        const auto start = std::chrono::steady_clock::now();
        matrix.generateMaze(game);
        const auto end = std::chrono::steady_clock::now();

        MatrixRenderer::displayMatrix(matrix, true);

        const std::chrono::duration<double> duration = end - start;

        std::cout << "Rows: " << rows << ", Cols: " << cols << ", Items: " << numOfItems << std::endl;
        std::cout << "\nMaze generation completed in " << duration.count() << " seconds.\n";

        game.playTheGame(matrix);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
