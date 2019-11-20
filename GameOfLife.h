// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	GameOfLife Class
// Description	:	Allows for the evolution from one frame to the next
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _GAMEOFLIFE_H_
#define _GAMEOFLIFE_H_


#include "Neighbourhood.h"	// for Neighbourhood member
#include "CellMatrix.h"		// for CellMatrix members
#include "Cell.h"			// for Cell::cellstate
#include "Rule.h"			// for Rule member


class GameOfLife
{
	CellMatrix mCurrentCM;
	CellMatrix mEvolvedCM;
	Rule mRule;
	Neighbourhood mHood;
public:
	GameOfLife(int, int);
	Cell::cellstate newCellState();
	Cell::cellstate applyRule(int rule, int sum);
	void importAndCenterCellmatrix(CellMatrix rleCM);
	void evolveMatrix();
	CellMatrix & cellmatrix();

};

#endif // !_GAMEOFLIFE_H_
