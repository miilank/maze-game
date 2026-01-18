#include "Item.h"

Item::Item(int r, int c, char t) : row(r), col(c), type(t) {}

int Item::getRow() { return row; }

int Item::getCol() { return col; }

char Item::getType() { return type; }