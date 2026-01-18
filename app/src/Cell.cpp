#include "Cell.h"

Cell::Cell() : type('.') {}

void Cell::setType(char newType)
{
	type = newType;
}

char Cell::getType() const
{
	return type;
}
