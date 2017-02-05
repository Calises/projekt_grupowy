#pragma once
#include "Cell.h"

class Map
{

	int w; //width (x)
	int d; //depth (y)
	//int h; // high (z)

	//tworzenie mapy
	//Cell **map3D;
	Cell **map3D;


public:
	Map(int ww = 20, int dd = 20);
	~Map();
	//void show(Cell **map3d);
	void show();
	void load(int ww, int dd);
	void setObstacle(int x, int y);
	void setStart(int x, int y);
	void setStop(int x, int y);
	int returnValue(int x, int y);
    CellState returnState(int x, int y);
    int getWidth() { return w; }
    int getDepth() { return d; }
    Cell **getMap3D() { return map3D; }
};
