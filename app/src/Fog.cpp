#include"Matrix.h"

Fog::Fog(int r, int c) : Item(r, c, 'F') {}

void Fog::activate(Matrix& matrix, Game& game) {
    if (game.getItemDuration() >= 0) MatrixRenderer::display3x3Matrix(matrix, true, game);
}