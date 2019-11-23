#include "Neighbourhood.h"


Neighbourhood::Neighbourhood(CellMatrix * cm, itCM * it)
	:mCM{ cm }, mIt{ it } {}



itCM Neighbourhood::up(itCM it)
{
	int i= std::distance(mCM->matrix().begin(), it);
	it += std::distance(mCM->matrix().begin(), it) < mCM->x() ? (mCM->y() - 1) * mCM->x()  : -(mCM->x());
	return it;
}


itCM Neighbourhood::down(itCM it)

{
	if (std::distance(mCM->matrix().end()- mCM->x(), it) >= 0)
		it -=  (mCM->y() - 1) * (mCM->x());
	else
		it += (mCM->x());

	//it-= std::distance(mCM->matrix().end(), it) <= mCM->x() ? (mCM->y() - 1) * mCM->x() : -(mCM->x());
	return it;
}


itCM Neighbourhood::left(itCM it)
{
	it += std::distance(mCM->matrix().begin(), it) % mCM->x() == 0 ? mCM ->x() - 1 : -1;
	return it;
}


itCM Neighbourhood::right(itCM it)
{
	it -= std::distance(mCM->matrix().end()-1, it) % mCM->x() == 0 ? mCM->x() - 1 : -1;
	return it;
}

//setter
void Neighbourhood::setIt(itCM * it)					{ mIt = it; }
void Neighbourhood::setCellMatrix(CellMatrix * cm)		{ mCM = cm; }


// getters

int Neighbourhood::sum()
{
	return (*up(left(*mIt))).state() + (*up(*mIt)).state() + (*up(right(*mIt))).state() + (*left(*mIt)).state() + (*right(*mIt)).state() + (*down(left(*mIt))).state() + (*down(*mIt)).state() + (*down(right(*mIt))).state();
}

Cell::cellstate  Neighbourhood::state() { return (**mIt).state(); }
