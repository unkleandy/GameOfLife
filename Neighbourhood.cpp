#include "Neighbourhood.h"



Neighbourhood::Neighbourhood(itCM it, CellMatrix cm)
	: mIt{ it } , mCM { cm } 
{}

//
// ! the cell matrix wrap functions are used to calculate the neighbourhoodand ensure that we are staying within the matrix, on the proper lines, and are used directionally

itCM Neighbourhood::up(itCM it)
{
	it -= mCM.x();
	if (it < mCM.vec().begin())		 { it+= mCM.x() * mCM.y(); }
	return it;
}
itCM Neighbourhood::down(itCM it)
{
	it += mCM.x();
	if (it >= mCM.vec().end()) { it -= mCM.x() * mCM.y(); }
	return it;
}

itCM Neighbourhood::left(itCM it)
{
	--it;
	if (std::distance(mCM.vec().begin(), it) % mCM.x() == mCM.x() - 1) { it += mCM.x(); }
	return it;
}

itCM Neighbourhood::right(itCM it)
{
	++it;
	if (std::distance(mCM.vec().begin(), it) % mCM.x() == 0) { it -= mCM.x(); }
	return it;
}


int Neighbourhood::sum()
{
	return *up(left(mIt)) + *up(mIt) + *up(right(mIt)) + *left(mIt) + *right(mIt) + *down(left(mIt)) + *down(mIt) + *down(right(mIt));
}
