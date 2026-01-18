#include "MatrixRenderer.h"

void MatrixRenderer::displayMatrix(Matrix& matrix, bool useColor, std::ostream& os) {
	int matrixRows = matrix.getMatrixRows();
	int matrixCols = matrix.getMatrixCols();
	Cell** mazeMatrix = matrix.getMatrix();
	for (int i = 0; i < matrixRows; i++) {
		for (int j = 0; j < matrixCols; j++) {
			if (useColor) {
				if (mazeMatrix[i][j].getType() == '#') {
					std::cout << "\033[38;5;18;48;5;240m" << mazeMatrix[i][j].getType() << "\033[0m";
				}
				else if (mazeMatrix[i][j].getType() == 'U' || mazeMatrix[i][j].getType() == 'I') {
					std::cout << "\033[38;5;117;48;5;240m" << mazeMatrix[i][j].getType() << "\033[0m";
				}
				else if (mazeMatrix[i][j].getType() == 'R') {
					std::cout << "\033[38;5;0;48;5;46m" << mazeMatrix[i][j].getType() << "\033[0m";
				}
				else if (mazeMatrix[i][j].getType() == 'P') {
					std::cout << "\033[38;5;203;48;5;15m" << mazeMatrix[i][j].getType() << "\033[0m";
				}
				else if (mazeMatrix[i][j].getType() == 'M') {
					std::cout << "\033[38;5;0;48;5;203m" << mazeMatrix[i][j].getType() << "\033[0m";
				}
				else {
					std::cout << "\033[38;5;15;48;5;240m" << mazeMatrix[i][j].getType() << "\033[0m";
				}

			}
			else {
				os << mazeMatrix[i][j].getType();
			}
		}
		os << std::endl;
	}
}

void MatrixRenderer::display3x3Matrix(Matrix& matrix, bool useColor, Game& game, std::ostream& os) {
	int startRow = std::max(game.getRobotRow() - 1, 0);
	int startCol = std::max(game.getRobotCol() - 1, 0);
	int endRow = std::min(game.getRobotRow() + 1, matrix.getMatrixRows() - 1);
	int endCol = std::min(game.getRobotCol() + 1, matrix.getMatrixCols() - 1);
	Cell** mazeMatrix = matrix.getMatrix();
	os << "Visibility Lost!" << std::endl;
	for (int i = startRow; i <= endRow; i++) {
		for (int j = startCol; j <= endCol; j++) {
			if (useColor) {
				if (matrix.getMatrix()[i][j].getType() == '#') {
					std::cout << "\033[38;5;18;48;5;240m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
				else if (matrix.getMatrix()[i][j].getType() == 'U' || matrix.getMatrix()[i][j].getType() == 'I') {
					std::cout << "\033[38;5;117;48;5;240m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
				else if (matrix.getMatrix()[i][j].getType() == 'R') {
					std::cout << "\033[38;5;0;48;5;46m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
				else if (matrix.getMatrix()[i][j].getType() == 'P') {
					std::cout << "\033[38;5;203;48;5;15m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
				else if (matrix.getMatrix()[i][j].getType() == 'M') {
					std::cout << "\033[38;5;0;48;5;203m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
				else {
					std::cout << "\033[38;5;15;48;5;240m" << matrix.getMatrix()[i][j].getType() << "\033[0m";
				}
			}
			else {
				os << mazeMatrix[i][j].getType();
			}
		}
		os << std::endl;
	}
}