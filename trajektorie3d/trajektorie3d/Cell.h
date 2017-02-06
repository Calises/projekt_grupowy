#pragma once
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

enum CellState {
    Wolna,
    Zajeta,
    Start,
    Koniec,
    Droga
};

class Cell
{
	int x;
	int y;
	int value;
    CellState state;

public:
	void show_cell();
    void change_cell(int val, CellState st);
	int cell_x();
	int cell_y();
	int cell_value();
    CellState cell_state();
    Cell(int xx = 1, int yy = 1, int val = 0, CellState st = Wolna);
	~Cell();

};
