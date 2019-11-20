#include "Neighbourhood.h"


Neighbourhood::Neighbourhood(CellMatrix cm)
	:mCM{ cm }, mIt{ cm.matrix().begin() }
{}


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

//setter
void Neighbourhood::setIt(const itCM & it)						{ mIt = it; }
void Neighbourhood::setCellMatrix(const CellMatrix & cm)		{ mCM = cm; }


// getters

int Neighbourhood::sum()
{
	return (*up(left(mIt))).state() + (*up(mIt)).state() + (*up(right(mIt))).state() + (*left(mIt)).state() + (*right(mIt)).state() + (*down(left(mIt))).state() + (*down(mIt)).state() + (*down(right(mIt))).state();
}

Cell::cellstate  Neighbourhood::state() { return (*mIt).state(); }
