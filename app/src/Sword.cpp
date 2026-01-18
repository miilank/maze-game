#include "Matrix.h"

Sword::Sword(int r, int c) : Item(r, c, 'S') {}

void Sword::activate(Matrix& matrix, Game& game)
{
	std::cout << "You can kill the Minotaur now: " << game.getItemDuration() << std::endl;
	if (game.minotaurKilled == false) {
		int minotaurR = game.getMinotaurRow();
		int minotaurC = game.getMinotaurCol();
		int robotR = game.getRobotRow();
		int robotC = game.getRobotCol();
		bool ifNeighbour = ((minotaurR == robotR && (minotaurC == robotC + 1 || minotaurC == robotC - 1)) ||
							(minotaurC == robotC && (minotaurR == robotR + 1 || minotaurR == robotR - 1)));

		if (ifNeighbour || (minotaurR == robotR && minotaurC == robotC)) {
			MatrixRenderer::displayMatrix(matrix, true);
			game.minotaurKilled = true;
			matrix.getMatrix()[minotaurR][minotaurC].setType('.');
			game.setMinotaurRow(-1);
			game.setMinotaurCol(-1);
			game.updatePosition(matrix, robotR, robotC, minotaurR, minotaurC, 'R');

			std::cout << "You killed the Minotaur!" << std::endl;
		}
	}
}
