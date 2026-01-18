#include "Game.h"

Game::Game(int robotRow, int robotCol, int minotaurRow, int minotaurCol) :
	robotRow(robotRow), robotCol(robotCol), minotaurRow(minotaurRow), minotaurCol(minotaurCol), 
	itemDuration(-1), isFog(false), hasSword(false), minotaurKilled(false), hasShield(false), hasHammer(false),
	robotNewRow(-1), robotNewCol(-1) {}

bool Game::moveRobot(Matrix& matrix, char direction) {
	int dRow = 0, dCol = 0;

	switch (direction) {
	case 'w': dRow = -1; break;
	case 's': dRow = 1; break;
	case 'a': dCol = -1; break;
	case 'd': dCol = 1; break;
	default: return false;
	}

	int newRow = getRobotRow() + dRow;
	int newCol = getRobotCol() + dCol;

	// if the robot has the hammer, inner walls must not be forbidden to step on, one problem: move is not valid so outer walls can be broken
	if (!isValidMove(matrix, newRow, newCol) && hasHammer == false) {
		return false;
	}
	// if the condition above cannot be processed, it means that the robot has the hammer, which means that we must prevent from breaking outer walls
	else if ((newRow == 0 || newRow == matrix.getMatrixRows() - 1 ||
			 newCol == 0 || newCol == matrix.getMatrixCols() - 1) && matrix.getMatrix()[newRow][newCol].getType() != 'I') {
		return false;
	}
	// otherwise, save new positions so we can break inner walls
	else {
		setRobotNewRow(newRow);
		setRobotNewCol(newCol);
	}

	handleParticularCells(matrix, newRow, newCol);
	updatePosition(matrix, getRobotRow(), getRobotCol(), newRow, newCol, 'R');
	return true;
}

bool Game::moveMinotaur(Matrix& matrix) {
	if (minotaurKilled) {
		return true;
	}
	int exitRow = matrix.getMatrixRows() - 1, exitCol = matrix.findExitColumn();

	if (exitCol == -1) {
		std::cout << "No exit found in the matrix!" << std::endl;
		return false;
	}
	randomMinotaurMove(matrix, exitRow, exitCol);
	if (checkMinotaurEatsRobot(matrix)) {
		return false;
	}
	if (getItemDuration() >= 0) {
		handleItemEffects(matrix);
	}
	return true;
}

void Game::playTheGame(Matrix& matrix) {
	char move;
	while (true) {
		displayControls();

		std::cin >> move;
		if (move == 'q') {
			std::ostringstream output;
			std::cout << "Exiting..." << std::endl;
			output << "Exiting..." << std::endl;
			MatrixRenderer::displayMatrix(matrix, false, output);
			std::string result = output.str();
			FileManager::writeToFile("result.txt", result);
			exit(0);
		}

		system("cls");

		if (moveRobot(matrix, move)) {
			if (!moveMinotaur(matrix)) {
				MatrixRenderer::displayMatrix(matrix, true);
				break;
			}
		}
		else {
			handleInvalidMove(matrix);
		}
		displayMatrix(matrix);
	}
}

bool Game::isValidMove(Matrix& matrix, int newRow, int newCol) {
	return newRow >= 0 && newRow < matrix.getMatrixRows() && newCol >= 0 && newCol < matrix.getMatrixCols() &&
		matrix.getMatrix()[newRow][newCol].getType() != '#' && matrix.getMatrix()[newRow][newCol].getType() != 'U';
}

void Game::handleParticularCells(Matrix& matrix, int newRow, int newCol) {
	char cellType = matrix.getMatrix()[newRow][newCol].getType();

	if (cellType == 'I') {
		std::ostringstream output;
		output << "You made it. You WON!" << std::endl;
		std::cout << "You made it. You WON!" << std::endl;
		updatePosition(matrix, getRobotRow(), getRobotCol(), newRow, newCol, 'R');
		MatrixRenderer::displayMatrix(matrix, true);
		MatrixRenderer::displayMatrix(matrix, false, output);
		std::string result = output.str();
		FileManager::writeToFile("result.txt", result);
		exit(0);

	}
	else if (cellType == 'P') {
		isFog = false;
		hasSword = false;
		hasShield = false;
		hasHammer = false;
		setItemDuration(3);
		int itemIndex = findItemIndex(matrix, newRow, newCol);
		if (itemIndex != -1) {
			Item* item = matrix.getItems()[itemIndex];
			matrix.setCurrentItem(item);

			if (item->getType() == 'F') {
				isFog = true;
			}
			else if (item->getType() == 'S') {
				hasSword = true;
			}
			else if (item->getType() == 'E') {
				hasShield = true;
			}
			else if (item->getType() == 'H') {
				hasHammer = true;
			}

			matrix.getItems().erase(matrix.getItems().begin() + itemIndex);
		}
	}
}

void Game::updatePosition(Matrix& matrix, int oldRow, int oldCol, int newRow, int newCol, char type) {
	matrix.getMatrix()[oldRow][oldCol].setType('.');
	if (type == 'R') {
		setRobotRow(newRow);
		setRobotCol(newCol);
	}
	else if (type == 'M') {
		setMinotaurRow(newRow);
		setMinotaurCol(newCol);
	}
	matrix.getMatrix()[newRow][newCol].setType(type);
}

void Game::handleItemEffects(Matrix& matrix) {
	if (getItemDuration() == 0) {
		isFog = false;
		hasHammer = false;
		return;
	}

	if (getItemDuration() == 1) {
		if (hasShield) {
			hasShield = false;
		}
		else if (hasSword) {
			hasSword = false;
			setItemDuration(0);
			matrix.getCurrentItem()->activate(matrix, *this);
			return;
		}
	}

	setItemDuration(getItemDuration() - 1);
	matrix.getCurrentItem()->activate(matrix, *this);
}

bool Game::checkMinotaurEatsRobot(Matrix& matrix) {
	int minotaurR = getMinotaurRow();
	int minotaurC = getMinotaurCol();
	int robotR = getRobotRow();
	int robotC = getRobotCol();

	bool ifNeighbour = ((robotR == minotaurR && (robotC == minotaurC + 1 || robotC == minotaurC - 1)) ||
						(robotC == minotaurC && (robotR == minotaurR + 1 || robotR == minotaurR - 1)));
	
	 if (hasShield) {
		 setRobotRow(getRobotRow());
		 setRobotCol(getRobotCol());
		 matrix.getMatrix()[getRobotRow()][getRobotCol()].setType('R');
	 }
	
	if ((!hasSword && !hasShield) &&
		(ifNeighbour || (minotaurR == robotR && minotaurC == robotC))) {
		if (isFog) {
			MatrixRenderer::display3x3Matrix(matrix, true, *this);
		}	
		setRobotRow(getRobotRow());
		setRobotCol(getRobotCol());
		matrix.getMatrix()[getRobotRow()][getRobotCol()].setType('R');
		MatrixRenderer::displayMatrix(matrix, true);
		updatePosition(matrix, minotaurR, minotaurC, robotR, robotC, 'M');
		std::ostringstream output;
		output << "Minotaur ate the Robot! You LOSE!" << std::endl;
		std::cout << "Minotaur ate the Robot! You LOSE!" << std::endl;
		MatrixRenderer::displayMatrix(matrix, false, output);
		std::string result = output.str();
		FileManager::writeToFile("result.txt", result);
		return true;
	}
	return false;
}

void Game::randomMinotaurMove(Matrix& matrix, int exitRow, int exitCol) {
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	bool minotaurTrapped = (matrix.getMatrix()[getMinotaurRow()][getMinotaurCol()+1].getType() == '#' &&
							matrix.getMatrix()[getMinotaurRow()][getMinotaurCol()-1].getType() == '#' &&
							matrix.getMatrix()[getMinotaurRow()+1][getMinotaurCol()].getType() == '#' &&
							matrix.getMatrix()[getMinotaurRow()-1][getMinotaurCol()].getType() == '#');

	while (!minotaurTrapped) {
		int randomDir = rand() % 4;
		int newRow = getMinotaurRow() + directions[randomDir][0];
		int newCol = getMinotaurCol() + directions[randomDir][1];

		if (isValidMove(matrix, newRow, newCol) &&
			!(newRow == exitRow && newCol == exitCol)) {
			updatePosition(matrix, getMinotaurRow(), getMinotaurCol(), newRow, newCol, 'M');
			break;
		}
	}
}

int Game::findItemIndex(Matrix& matrix, int row, int col) const {
	for (int i = 0; i < matrix.getNoOfItems(); i++) {
		if (matrix.getItems()[i]->getRow() == row && matrix.getItems()[i]->getCol() == col) {
			return i;
		}
	}
	return -1;
}

void Game::displayControls() {
	std::cout << std::endl << "Controls: w(up), s(down), a(left), d(right), q(quit)" << std::endl;
	std::cout << "Enter move: ";
}

void Game::displayMatrix(Matrix& matrix) {
	if (!isFog) {
		MatrixRenderer::displayMatrix(matrix, true);
	}
}

void Game::handleInvalidMove(Matrix& matrix) {
	if (isFog) {
		MatrixRenderer::display3x3Matrix(matrix, true, *this);
	}
    std::cout << "Invalid move! Try again." << std::endl;
}

int Game::getRobotRow() { 
	return this->robotRow;
}

void Game::setRobotRow(int row) {
	this->robotRow = row;
}

int Game::getRobotCol() { 
	return this->robotCol;
}

void Game::setRobotCol(int col) {
	this->robotCol = col;
}

int Game::getRobotNewRow() {
	return this->robotNewRow;
}

void Game::setRobotNewRow(int row) {
	this->robotNewRow = row;
}

int Game::getRobotNewCol() {
	return this->robotNewCol;
}

void Game::setRobotNewCol(int col) {
	this->robotNewCol = col;
}

int Game::getMinotaurRow() {
	return this->minotaurRow;
}

void Game::setMinotaurRow(int row) {
	this->minotaurRow = row;
}

int Game::getMinotaurCol() {
	return this->minotaurCol;
}

void Game::setMinotaurCol(int col) {
	this->minotaurCol = col;
}

void Game::setItemDuration(int itemDuration) {
	this->itemDuration = itemDuration;
}

int Game::getItemDuration() {
	return this->itemDuration;
}