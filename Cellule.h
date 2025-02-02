#pragma once
#include <utility>
#include <iostream>
using namespace std;
enum CellState //pour decrire l'etat d'une cellule
{
	wall=1,
	start,
	out,
	none,
	inRaod,
	visited
};
// Structure pour stocker une cellule frontière
struct FrontierCell 
{
	int x, y;
	int px, py; // Coordonnées du parent pour relier le chemin
};
class Cellule
{
private:
	pair<int, int> position;
	CellState state;

public:
	Cellule(pair<int, int>pos, CellState etat = none);
	void setState(CellState state);
	CellState getState() const;
	pair<int, int> getPosition() const;
};

