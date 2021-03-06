#include "Cell.h"
#include <iostream>
#include <windows.h>
#include <string>

Cell::Cell(int xx, int yy, int zz, int val, CellState st)
{
	x = xx;
	y = yy;
    z = zz;
	value = val;
	state = st;
}


Cell::~Cell()
{
}

void Cell::show_cell()
{
    cout << "x: " << x << " y: " << y << " z: " << z << " val: " << value << " st: " << state << endl;
}
void Cell::change_cell(int val, CellState st)
{
	value = val;
	state = st;
}
int Cell::cell_x()
{
	return x;
}
int Cell::cell_y()
{
	return y;
}
int Cell::cell_z()
{
    return z;
}
int Cell::cell_value()
{
	return value;
}
CellState Cell::cell_state()
{
	return state;
}