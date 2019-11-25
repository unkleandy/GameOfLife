// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	Model Class
// Description	:	
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "CellMatrix.h"
#include "Rule.h"
#include "GameOfLife.h"

#include <string>


class Model
{
private:
	Rule mRule;
	GameOfLife mGoL;
	std::vector<Rule> mRules;
	std::vector<std::string>mRles;

public:
	Model(int dimX, int dimY);

	void update();
	void nextRule();
	void showRule();
	void reinitialise();
	void randomiseMatrix(double percentage);
	void nextRle();
	void sameRle();
	void prevRle();
	CellMatrix & cellmatrix();
	GameOfLife & gol();
	
};


#endif // !_MODEL_H_
