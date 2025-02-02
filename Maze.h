#pragma once
#include"Cellule.h"
#include <vector>
#include <json/json.h>
#include "httplib.hpp"
//#include <uwebsockets/App.h>
class Maze
{
private:
	vector<vector<Cellule>> grid;//la grille de cellules
	int width, height;// la huateur et largeur de la grille
	pair<int, int> start; //position de l'entee du labyrinthe
	pair<int, int> end;// position de la sortie du labyrinthe
public:
	Maze(int h, int w);
	void GenerateMaze();
	void setStart(pair<int, int> start);
	void setEnd(pair<int, int> end);
	void displayMaze() const;
	bool isValid(int x, int y) const;
	vector<pair<int, int>> solveDijkstra(vector<pair<int, int>>& steps)const;
	vector<pair<int, int>> solveBFS(vector<pair<int, int>>& steps)const;
	vector<vector<Cellule>> getGrid() const;
	void setGrid(vector<vector<Cellule>> newGrid);
};

