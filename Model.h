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


class Model
{
private:
	CellMatrix mCM;
	Rule rule;

public:
	Model();
	~Model();
	void setCellMatrix(int, int);
	void update();
	void nextrule();
	void reinitialise();
	CellMatrix cellmatrix() { return mCM; }
};


#endif // !_MODEL_H_
