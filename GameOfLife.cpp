#include "GameOfLife.h"


GameOfLife::GameOfLife(int x, int y)
	:
	mCM0{ x, y },
	mCM1{ x, y },
	mHood{ &mCM0, &itCM{mCM0.matrix().begin()} },
	mCurrentCM { &mCM0 },
	mEvolvedCM { &mCM1 },
	mRule{ std::vector<int>{3}, std::vector<int>{2,3} }
{ mRule.setRule(std::vector<int>{3}, std::vector<int>{2,3}); }

Cell::cellstate GameOfLife::newCellState()
{
	if(mHood.state())	{ return applyRule( mRule.survive(), mHood.sum()); }
	else				{ return applyRule( mRule.born(), mHood.sum()); }
}

Cell::cellstate GameOfLife::applyRule(int rule, int sum) { return (Cell::cellstate) (rule >> sum & 1); }

void GameOfLife::importAndCenterCellmatrix(CellMatrix rleCM)
{
	mCurrentCM->initializeMatrix0();
	int xSurplus { mCurrentCM->x() - rleCM.x() };
	int yBegin { (mCurrentCM->y() - rleCM.y()) / 2 };
	
	//sets the iterator at the beginning position to center the imported CellMatrix
	itCM itGoL{ (mCurrentCM->matrix().begin() + yBegin * mCurrentCM->x() + (int) xSurplus/2) };
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
		// skips to the next line at the proper offset in the larger matrix
		itGoL += xSurplus;
	}

}

void GameOfLife::evolveMatrix()
{
	itCM currentCell { mCurrentCM->matrix().begin() };
	itCM evolvedCell { mEvolvedCM->matrix().begin() };

	mHood.setCellMatrix(mCurrentCM);
	mHood.setIt(&currentCell);

	while (currentCell != mCurrentCM->matrix().end())
	{
		(*evolvedCell).setState(newCellState());
		++currentCell;
		++evolvedCell;
	}

	mTempCM = mCurrentCM;
	mCurrentCM = mEvolvedCM;
	mEvolvedCM = mTempCM;
}


CellMatrix & GameOfLife::cellmatrix() { return  (*mCurrentCM); }

