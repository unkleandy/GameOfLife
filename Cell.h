// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	Cell Class
// Description	:	Basic unit of the CellMatrix with some member methods that allow the use of CellMatrix::travel
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	
#include "RandomUtil.h"		// required for : RandomUtil::generateEvent 

#pragma once
#ifndef _CELL_H_ 
#define _CELL_H_

const unsigned char cellActive{ 219 };
const char cellInactive{ ' ' };


class Cell
{
public:
	enum cellstate : bool
	{
		inactive,
		active
	};
private:
	cellstate mState;

public:

	Cell();
	Cell(cellstate cs);
	~Cell();
	//methods
	cellstate state();

	void setState(cellstate cs);
	void setStateActive();
	void show();
	void randomize(double probability);
};

#endif // !_CELL_H_

