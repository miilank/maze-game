#include "Matrix.h"

Matrix::Matrix(int rows, int cols, int noOfItems, int moveCount) : rows(rows), cols(cols), noOfItems(noOfItems), currentItem(nullptr) {
	setMatrix(new Cell * [getMatrixRows()]);
	for (int i = 0; i < getMatrixRows(); i++) {
		getMatrix()[i] = new Cell[getMatrixCols()];
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < getMatrixRows(); i++) {
		delete[] getMatrix()[i];
	}
	delete[] getMatrix();
}

void Matrix::generateMaze(Game& game) {
	initializeMatrix();
	setExteriorWalls();
	setEntranceAndExit(game);
	int optimalWalls = calculateOptimalWalls();
	generateInnerWalls(game, optimalWalls);
	setItems(game);
}

void Matrix::initializeMatrix() {
	for (int i = 0; i < getMatrixRows(); i++) {
		for (int j = 0; j < getMatrixCols(); j++) {
			getMatrix()[i][j].setType('.');
		}
	}
}

void Matrix::setExteriorWalls() {
	for (int i = 0; i < getMatrixRows(); i++) {
		getMatrix()[i][0].setType('#');
		getMatrix()[i][getMatrixCols() - 1].setType('#');
	}
	for (int i = 0; i < getMatrixCols(); i++) {
		getMatrix()[0][i].setType('#');
		getMatrix()[getMatrixRows() - 1][i].setType('#');
	}
}

void Matrix::setEntranceAndExit(Game& game) {
	getMatrix()[0][game.getRobotCol()].setType('U');

	int exitCol;
	do {
		exitCol = rand() % getMatrixCols();
	} while (!(exitCol != 0 && exitCol != getMatrixCols() - 1));
	getMatrix()[getMatrixRows() - 1][exitCol].setType('I');
}

int Matrix::calculateOptimalWalls(){
	int minWalls = 2 * (getMatrixRows() + getMatrixCols());
	int maxWalls = calculateMaxWalls(getMatrixRows(), getMatrixCols());
	return (minWalls + maxWalls) / 2;
}

int Matrix::calculateMaxWalls(int rows, int cols) {
	int matrixRows = getMatrixRows();
	int matrixCols = getMatrixCols();
	int totalCells = matrixRows * matrixCols;
	int minPathLength = matrixRows + matrixCols - 2;

	double occupancyRate;
	if (totalCells <= 300) {
		occupancyRate = 0.35;
	}
	else if (totalCells <= 450) {
		occupancyRate = 0.49;
	}
	else if (totalCells <= 1000) {
		occupancyRate = 0.58;
	}
	else {
		occupancyRate = 0.63;
	}

	int maxWalls = (int)std::ceil(occupancyRate * (totalCells - minPathLength));
	return maxWalls;
}

int Matrix::calculateOptimalNumOfItems() {
	int matrixRows = getMatrixRows();
	int matrixCols = getMatrixCols();
	int totalCells = matrixRows * matrixCols;
	double optimalPercent;

	if (totalCells <= 100) {
		optimalPercent = 0.1;
	}
	else if (totalCells <= 300) {
		optimalPercent = 0.2;
	}
	else if (totalCells <= 600) {
		optimalPercent = 0.25;
	}
	else {
		optimalPercent = 0.3;
	}
	int maxNumOfItems = matrixRows * matrixCols - 2 * (matrixRows + matrixCols) - calculateOptimalWalls() - 2;
	return  (int)std::ceil(optimalPercent * maxNumOfItems);
}

bool Matrix::generateInnerWalls(Game& game, int remainingWalls) {
	while (true) {
		// do not count edges
		for (int i = 1; i < getMatrixRows()-1; i++) {
			for (int j = 1; j < getMatrixCols()-1; j++) {
				matrix[i][j].setType('.');
			}
		}

		int wallsPlaced = 0;
		while (wallsPlaced < remainingWalls) {
			// 1+ in the case of 0, -2 for not counting edges
			int row = 1 + rand() % (getMatrixRows() - 2);
			int col = 1 + rand() % (getMatrixCols() - 2);

			if (matrix[row][col].getType() == '#') {
				continue;
			}

			matrix[row][col].setType('#');
			wallsPlaced++;
		}

		if (hasPath(game)) {
			return true;
		}
	}
}

bool Matrix::hasPath(Game& game) {
	int entranceRow = 0, entranceCol = game.getRobotCol();
	int exitRow = getMatrixRows() - 1, exitCol = findExitColumn();


	if (exitCol == -1) {
		std::cout << "No exit found in the matrix!" << std::endl;
		return false;
	}

	bool** visited = allocateVisitedMatrix();
	bool pathExists = bfsPathExists(entranceRow, entranceCol, exitRow, exitCol, visited);
	freeVisitedMatrix(visited);
	return pathExists;
}

int Matrix::findExitColumn() {
	for (int j = 0; j < getMatrixCols(); j++) {
		if (getMatrix()[getMatrixRows() - 1][j].getType() == 'I') {
			return j;
		}
	}
	return -1;
}

bool** Matrix::allocateVisitedMatrix() {
	int matrixRows = getMatrixRows();
	int matrixCols = getMatrixCols();
	bool** visited = new bool* [matrixRows];
	for (int i = 0; i < matrixRows; i++) {
		visited[i] = new bool[matrixCols] {false};
	}
	return visited;
}

void Matrix::freeVisitedMatrix(bool** visited) {
	int matrixRows = getMatrixRows();
	for (int i = 0; i < matrixRows; i++) {
		delete[] visited[i];
	}
	delete[] visited;
}

bool Matrix::bfsPathExists(int entranceRow, int entranceCol, int exitRow, int exitCol, bool** visited) {
	std::queue<std::pair<int, int>> q;
	q.push({ entranceRow, entranceCol });
	visited[entranceRow][entranceCol] = true;

	const int dirRow[] = { -1, 1, 0, 0 };
	const int dirCol[] = { 0, 0, -1, 1 };

	while (!q.empty()) {
		std::pair<int, int> current = q.front();
		int currentRow = current.first;
		int currentCol = current.second;
		q.pop();

		if (currentRow == exitRow && currentCol == exitCol) {
			return true;
		}

		for (int i = 0; i < 4; i++) {
			int newRow = currentRow + dirRow[i];
			int newCol = currentCol + dirCol[i];

			if (isValidCell(newRow, newCol, visited)) {
				visited[newRow][newCol] = true;
				q.push({ newRow, newCol });
			}
		}
	}
	return false;
}

bool Matrix::isValidCell(int newRow, int newCol, bool** visited)
{
	return newRow >= 0 && newRow < getMatrixRows() && newCol >= 0 && newCol < getMatrixCols() &&
		!visited[newRow][newCol] && getMatrix()[newRow][newCol].getType() != '#';
}

void Matrix::setItems(Game& game) {
	getMatrix()[game.getRobotRow()][game.getRobotCol()].setType('R');
	setMinotaurPosition(game);
	placeSpecialItems(game);
}

void Matrix::setMinotaurPosition(Game& game) {
	int matrixRows = getMatrixRows();
	int matrixCols = getMatrixCols();
	Cell** mazeMatrix = getMatrix();

	std::vector<std::pair<int, int>> validPositions;
	for (int i = (int)std::ceil(matrixRows / 2); i < matrixRows; i++) {
		for (int j = 0; j < matrixCols; j++) {
			if (mazeMatrix[i][j].getType() == '.') {
				validPositions.emplace_back(i, j);
			}
		}
	}

	if (validPositions.empty()) {
		std::cerr << "Error: No valid positions for Minotaur." << std::endl;
		return;
	}

	std::pair<int, int> chosenPosition = validPositions[rand() % validPositions.size()];
	game.setMinotaurRow(chosenPosition.first);
	game.setMinotaurCol(chosenPosition.second);
	mazeMatrix[game.getMinotaurRow()][game.getMinotaurCol()].setType('M');
}

void Matrix::placeSpecialItems(Game& game) {
	int matrixRows = getMatrixRows();
	int matrixCols = getMatrixCols();
	Cell** mazeMatrix = getMatrix();
	int numOfItems = getNoOfItems();

	int cnt = 0;
	while (cnt < numOfItems) {
		int effectRow = rand() % matrixRows;
		int effectCol = rand() % matrixCols;

		if (mazeMatrix[effectRow][effectCol].getType() == '.') {
			mazeMatrix[effectRow][effectCol].setType('P');

			int randEffect = rand()%4;
			Item* item = nullptr;
			switch (randEffect) {
			case 0: item = new Fog(effectRow, effectCol); break;
			case 1: item = new Sword(effectRow, effectCol); break;
			case 2: item = new Shield(effectRow, effectCol); break;
			case 3: item = new Hammer(effectRow, effectCol); break;
			}
			setItems(item);
			cnt++;
		}
	}
}

Cell** Matrix::getMatrix()
{
	return matrix;
}

void Matrix::setMatrix(Cell** matrix) {
	this->matrix = matrix;
}

int Matrix::getMatrixRows()
{
	return rows;
}

int Matrix::getMatrixCols()
{
	return cols;
}

int Matrix::getNoOfItems()
{
	return this->noOfItems;
}

Item* Matrix::getCurrentItem()
{
	return this->currentItem;
}

void Matrix::setCurrentItem(Item* item)
{
	this->currentItem = item;
}

std::vector<Item*>& Matrix::getItems()
{
	return this->items;
}

void Matrix::setItems(Item* item) {
	this->items.push_back(item);
}
