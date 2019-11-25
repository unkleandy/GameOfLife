
#include "CellMatrix.h"
#include "Neighbourhood.h"
#include <cassert>				//for assert for CellMatrix::travelCellMatrix
#include <iostream>				//for cout in CellMatrix show



// constructors
CellMatrix::CellMatrix() :mDimX{}, mDimY{}, mMatrix{}{}

CellMatrix::CellMatrix(int x, int y) :mDimX{ x }, mDimY{ y }, mMatrix{ (x*y), Cell(Cell::inactive) } {}


void CellMatrix::initializeMatrix0()
{
	std::fill(mMatrix.begin(), mMatrix.end(), Cell(Cell::inactive));
}


void CellMatrix::setSize(int x, int y)
{
	mDimX = x;
	mDimY = y;
	mMatrix.resize(x*y);
	initializeMatrix0();
}


// member methods that use travelCellMatrix
//void CellMatrix::randomizeMatrix()	{ travelCellMatrix(&Cell::randomize, mMatrix.begin(), mMatrix.end()); }


void CellMatrix::randomizeMatrix(double pourcentage)				//{ travelCellMatrix(&Cell::show, mMatrix.begin(), mMatrix.end()); }
{
	itCM currentCell{ mMatrix.begin() };
	for (int j{}; j < mDimY; ++j)
	{
		for (int i{ 0 }; i < mDimX; ++i)
		{
			(*currentCell).randomize(pourcentage);
			++currentCell;
		}
		std::cout << std::endl;
	}
}


void CellMatrix::show()				//{ travelCellMatrix(&Cell::show, mMatrix.begin(), mMatrix.end()); }
{
	itCM currentCell{ mMatrix.begin() };
	for (int j{}; j < mDimY; ++j)
	{
		for (int i{ 0 }; i < mDimX; ++i)
		{
			(*currentCell).show();
			++currentCell;
		}
		std::cout << std::endl;
	}
}

void CellMatrix::travelCellMatrix(void(Cell::*task)(), itCM currentCell, itCM finish)
{
	assert(finish < mMatrix.end());

	while (currentCell != finish) 
	{
			((*currentCell).*task)();
			++currentCell;
	}
}


// getters

int CellMatrix::x() { return mDimX; }

int CellMatrix::y() { return mDimY; }

std::vector<Cell> & CellMatrix::matrix() { return mMatrix; }