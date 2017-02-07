#pragma once
#include "Cell.h"
#include <vector>

class Map
{

	int w; //width (x)
	int d; //depth (y)
	int h; // height (z)

	//tworzenie mapy
	Cell ***map3D;


public:
	Map(int ww = 20, int dd = 20, int hh = 20);
	~Map();
	//void show(Cell **map3d);
	void show();
	void load(int ww, int dd, int hh);
	void setObstacle(int x, int y, int z = 1);
    void setStart(int x, int y, int z = 1);
    void setStop(int x, int y, int z = 1);
    void setEmpty(int x, int y, int z = 1);
    void setTrace(int x, int y, int z = 1);
    void setBuffer(int x, int y, int z = 1);
	Cell getStart();
	Cell getStop();
	std::vector <Cell> getObstacleList();
    int returnValue(int x, int y, int z);
    CellState returnState(int x, int y, int z);
    int getWidth() { return w; }
    int getDepth() { return d; }
    int getHeight() { return h; }
    Cell ***getMap3D() { return map3D; }
    void updateBuffer(int _buffSize);
    void Map::buildUpBuffer(int _x, int _y, int _z, int _size);
};
