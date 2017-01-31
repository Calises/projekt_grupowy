#include "map.h"
#include "Cell.h"
#include <iomanip>
#include <iostream>

using namespace std;


Map::Map(int ww, int dd)
{
	w = ww;
	d = dd;
	load(w, d);
}


Map::~Map()
{

	for (int i = 0; i < w + 2; i++) {
		delete[] map3D[i];
	}
	delete[] map3D;

}

void Map::load(int ww, int dd)
{
	//zwiekszenie wymiarow, zeby zrobic dookola "blokade"
	ww = ww + 2;
	dd = dd + 2;

	//tworzenie mapy
	//Cell **map3D = new Cell *[ww]; - przez to nie mog³am wywolac show, bez przeslania tablicy
	map3D = new Cell *[ww];
	for (int i = 0; i < ww; i++)
	{
		map3D[i] = new Cell[dd];
		for (int j = 0; j < dd; j++)
		{
			// ustawienie ramki dookola mapy
			if (i == 0 || i == ww - 1 || j == 0 || j == dd - 1) {
				map3D[i][j] = Cell(i, j, -1, 'f');
			}
			else map3D[i][j] = Cell(i, j, 100, 'e');
			//map3D[i][j].show_cell(); - CZEMU TO NIE DZIALA ?
		}
	}

	for (int i = 0; i < ww; i++)
	{
		for (int j = 0; j < dd; j++)
		{
			map3D[i][j].show_cell();
		}
	}




	//rysowanie
	//show(map3D);
	//show();


	// MAPA 3D
	/*int ***arr3D = new int**[X];
	for (int i = 0; i<X; i++) {
	arr3D[i] = new int*[Y];
	for (int j = 0; j<Y; j++) {
	arr3D[i][j] = new int[Z];
	for (int k = 0; k<Z; k++) {
	arr3D[i][j][k] = 0;
	*/

}

//void map::show(Cell **map3d)
void Map::show()
{

	for (int i = 0; i < d + 2; i++)
	{
		for (int j = 0; j < w + 2; j++)
		{
			if (map3D[j][i].cell_value() == -1)
				cout << "| " << setw(3) << "x" << " ";
			else cout << "| " << setw(3) << 100 << " "; // map3D[j][i].cell_value() << " ";
		}
		cout << endl;

	}

	system("PAUSE");
}

void Map::setObstacle(int x, int y)
{
	map3D[x][y].change_cell(x, y, -1, 'f');
}
void Map::setStart(int x, int y)
{
	map3D[x][y].change_cell(x, y, 1, 's');
}
void Map::setStop(int x, int y)
{
	map3D[x][y].change_cell(x, y, 100, 'd');
}
//pomocnicza
int Map::returnValue(int x, int y)
{
	return map3D[x][y].cell_value();
}
