#include "Matrix.h"

Shield::Shield(int r, int c) : Item(r, c, 'E') {}

void Shield::activate(Matrix& matrix, Game& game)
{
	std::cout << "You are protected from the Minotaur now: " << game.getItemDuration() << std::endl;
}