#include "map.h"
#include "Cell.h"
#include <iomanip>
#include <iostream>
#include <vector>

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
	//Cell **map3D = new Cell *[ww]; - przez to nie mog�am wywolac show, bez przeslania tablicy
	map3D = new Cell *[ww];
	for (int i = 0; i < ww; i++)
	{
		map3D[i] = new Cell[dd];
		for (int j = 0; j < dd; j++)
		{
			// ustawienie ramki dookola mapy
			if (i == 0 || i == ww - 1 || j == 0 || j == dd - 1) {
				map3D[i][j] = Cell(i, j, -1, Zajeta);
			}
			else map3D[i][j] = Cell(i, j, 100, Wolna);
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
	map3D[x][y].change_cell(-1, Zajeta);
}
void Map::setStart(int x, int y)
{
	map3D[x][y].change_cell(1, Start);
}
void Map::setStop(int x, int y)
{
	map3D[x][y].change_cell(100, Koniec); //? 100 czy 0
}

void Map::setEmpty(int x, int y)
{
	map3D[x][y].change_cell(100, Wolna);
}

void Map::setTrace(int x, int y)
{
    map3D[x][y].change_cell(200, Droga);
}

Cell Map::getStart() {
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= d; j++) {
			Cell cell = map3D[i][j];
			if (cell.cell_state() == Start) {
				return cell;
			}
		}
	}
}

Cell Map::getStop() {
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= d; j++) {
			Cell cell = map3D[i][j];
			if (cell.cell_state() == Koniec) {
				return cell;
			}
		}
	}
}

std::vector <Cell> Map::getObstacleList() {
	std::vector <Cell> obstacleCell;
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= d; j++) {
			Cell cell = map3D[i][j];
			if (cell.cell_state() == Zajeta) {
				obstacleCell.push_back(cell);
			}
		}
	}
	return obstacleCell;
}

//pomocnicza
int Map::returnValue(int x, int y)
{
	return map3D[x][y].cell_value();
}
CellState Map::returnState(int x, int y)
{
    return map3D[x][y].cell_state();
}
