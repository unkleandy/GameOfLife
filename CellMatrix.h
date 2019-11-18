
#pragma once
#ifndef _CELLMATRIX_H_
#define _CELLMATRIX_H_

#include <vector>		//for vector
#include "Cell.h"



class Rule {
private:
	int mRule;

public:
	Rule() : mRule{ 0 } {}
	int rule() { return mRule; }
	void nextRule() { ++mRule; }
};

using itCM = std::vector<Cell>::iterator;

class CellMatrix {
private:
	int mDimX;
	int mDimY;
	std::vector<Cell> mMatrix;
public:
	CellMatrix();
	CellMatrix(int x, int y);
	std::vector<Cell> vec() { return mMatrix; }
	void setSize(int, int);
	void initializeMatrix0();
	void randomizeMatrix();
	void travelCellMatrix(void(Cell::*task)(), itCM start, itCM finish);
	void show();
	int x();
	int y();
	std::vector<Cell> matrix();
};

#endif // !_CELLMATRIX_H_