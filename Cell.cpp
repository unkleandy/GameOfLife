#include "Cell.h"
#include <random>					// for Cell::randomize()
#include <iostream>						// for testing Cell::show()


Cell::Cell()						:mState{} {}

Cell::Cell(cellstate cs)			: mState{ cs }	{}

Cell::~Cell()						{}


// methods

Cell::cellstate Cell::state()		{ return mState; }

void Cell::setState(cellstate cs)	{ mState = cs; }

void Cell::setStateActive()			{ mState = active; }

void Cell::show()					{ std::cout<< (mState ? cellActive : cellInactive); }

//void Cell::invert()					{ mState = (cellstate)!state; }

void Cell::randomize()				{ mState = (cellstate)(rand() & 1); }



