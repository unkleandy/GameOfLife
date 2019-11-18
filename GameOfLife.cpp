#include "GameOfLife.h"


GameOfLife::GameOfLife(int x, int y)	:mCurrentCM{x, y}, mNewCM{x, y}, mHood {mCurrentCM}	{}

Cell::cellstate GameOfLife::newCellState()
{
	if(mHood.state())	{ return applyRule( mRule.survive(), mHood.sum()); }
	else				{ return applyRule( mRule.born(), mHood.sum()); }
}

Cell::cellstate GameOfLife::applyRule(int rule, int sum) { return (Cell::cellstate) (rule >> sum & 1); }

void GameOfLife::importAndCenterCellmatrix(CellMatrix rleCM)
{
	mCurrentCM.initializeMatrix0();
	int xSurplus { mCurrentCM.x() - rleCM.x() };
	int yBegin { mCurrentCM.y() - rleCM.y() / 2 };

	//sets the iterator at the beginning position to center the imported CellMatrix
	itCM itGoL{ mCurrentCM.matrix().begin()+ yBegin*mCurrentCM.x()+xSurplus/2};
	itCM itRLE{ rleCM.matrix().begin() };
	for (int j{}; j < rleCM.y(); ++j)
	{
		// copies a line
		for (int i{}; i<rleCM.x(); ++i)
		{
			(*itGoL).setState((*itRLE).state());
			++itGoL;
			++itRLE;
		}
		// skips to the next line in the larger matrix
		itGoL += xSurplus;
	}
}

void GameOfLife::evolveMatrix()
{
	itCM currentCell { mCurrentCM.matrix().begin() };
	itCM evolvedCell { mNewCM.matrix().begin() };

	while (currentCell != mCurrentCM.matrix().end())
	{
		mHood.it(currentCell);
		(*evolvedCell).setState(newCellState());
		++currentCell;
		++evolvedCell;
	}
}
