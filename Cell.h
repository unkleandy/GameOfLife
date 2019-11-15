#pragma once
#ifndef _CELL_H_ 
#define _CELL_H_

const char cellActive{ '*' };
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

	Cell(cellstate cs) : mState{ cs } {}
	cellstate state() { return mState; }
	void setState(cellstate cs) { mState = cs; }
	//void invert()									{ mState = (cellstate)!state; }
	void show() { printf("%c", mState ? cellActive : cellInactive); }
	void randomize() { mState = (cellstate)(rand() & 1); }

};

#endif // !_CELL_H_

