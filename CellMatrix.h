#pragma once

#ifndef _CELLMATRIX_H_
#define _CELLMATRIX_H_

#include <vector>		//for vector



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
	int mX;
	int mY;
	std::vector<Cell> mVec;
public:
	CellMatrix();
	CellMatrix(int x, int y);
	std::vector<Cell> vec() { return mVec; }
	void setsize(int, int);
	void initializeMatrix0();
	void initialiseFirstRow();
	void travelCellMatrix(void(Cell::*task)(), itCM, itCM);
	void applyRule(itCM start, itCM finish, Rule r);
	int findCombination(itCM index);
	int x();
	int y();
	std::vector<Cell> vec()
};






#endif // _CELLMATRIX_H_