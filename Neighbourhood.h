// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	Neighbourhood Class
// Description	:	
// Author		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _NEIGHBOURHOOD_H_
#define _NEIGHBOURHOOD_H_
#include "CellMatrix.h"

class Neighbourhood
{
private:
	CellMatrix mCM;
	itCM mIt;

	itCM up(itCM it);
	itCM down(itCM it);
	itCM left(itCM it);
	itCM right(itCM it);


	
public:
	Neighbourhood(CellMatrix);
	//getters
	int sum();
	Cell::cellstate state();
	// setters
	void setIt(const itCM &);
	void setCellMatrix(const CellMatrix &);
};

#endif // !_NEIGHBOURHOOD_H_


