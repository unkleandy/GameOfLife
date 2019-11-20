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


class Model
{
private:
	CellMatrix mCM;
	Rule mRule;
	GameOfLife mGoL;

public:
	Model();
	void setCellMatrix(int, int);
	void update();
	void nextrule();
	void reinitialise();
	CellMatrix & cellmatrix();
	GameOfLife & gol();
	
};


#endif // !_MODEL_H_
