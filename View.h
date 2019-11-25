// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	View Class
// Description	:	
// Autrice		:	
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _VIEW_H_
#define _VIEW_H_

#include <iterator>

#include "./Console/Console.h"
#include "./Console/ConsoleColor.h"
#include "CellMatrix.h"


class View 
{
private:
	ConsoleWriter & mWriter;
	std::vector< ConsoleColor::Text> mTextColors;
	std::vector< ConsoleColor::Background> mBackgroundColors;
	std::vector< ConsoleColor::Text>::iterator mTextColorIt;
	std::vector< ConsoleColor::Background>::iterator mBackgroundColorIt;
	ConsoleColor::Text mCurrentTextColor;
	ConsoleColor::Background mCurrentBackgroundColor;
	
public:
	View();
	void showCurrent(CellMatrix & currentCellMatrix);
	void toggleBackgroundColor();
	void changeTextColor();
};


#endif // !_VIEW_H_
