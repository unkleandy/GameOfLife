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
	Neighbourhood();

	~Neighbourhood();
	int sum();
};

#endif // !_NEIGHBOURHOOD_H_


