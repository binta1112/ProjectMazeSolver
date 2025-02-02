#include "Cellule.h"

Cellule::Cellule(pair<int, int> pos, CellState etat):position(pos),state(etat)
{
}

void Cellule::setState(CellState state)
{
    this->state = state;
}

CellState Cellule::getState() const
{
    return this->state;
}

pair<int, int> Cellule::getPosition() const
{
    return this->position;
}
