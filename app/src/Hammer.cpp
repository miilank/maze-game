#include "Matrix.h"

Hammer::Hammer(int r, int c) : Item(r, c, 'H') {}

void Hammer::activate(Matrix& matrix, Game& game)
{	
	if(game.hasHammer) {
		std::cout << "You can destroy walls now: " << game.getItemDuration() + 1 << std::endl;
		int robotRow = game.getRobotRow();
		int robotCol = game.getRobotCol();
		int robotNewRow = game.getRobotNewRow();
		int robotNewCol = game.getRobotNewCol();

		game.updatePosition(matrix, robotRow, robotCol, robotNewRow, robotNewCol, 'R');
	}
}

