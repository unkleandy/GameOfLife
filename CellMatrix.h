// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	CellMatrix Class
// Description	:	
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _CELLMATRIX_H_
#define _CELLMATRIX_H_

#include <vector>		//for vector
#include "Cell.h"


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