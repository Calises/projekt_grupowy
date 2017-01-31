#pragma once
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

class Cell
{
	int x;
	int y;
	int value;
	char state; // e- wolna, f-zajeta, s-start, d-koniec

public:
	void show_cell();
	void change_cell(int xx, int yy, int val, char st);
	int cell_x();
	int cell_y();
	int cell_value();
	char cell_state();
	Cell(int xx = 1, int yy = 1, int val = 0, char st = 'e');
	~Cell();

};
