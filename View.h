// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	View Class
// Description	:	
// Auteurs		:	Andréa Cohem & Cito Buhendwa
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _VIEW_H_
#define _VIEW_H_

#include <iterator>

#include "./Console/Console.h"
#include "./Console/ConsoleColor.h"
#include "CellMatrix.h"
#include "ColorManager.h"


class View 
{
private:
	ConsoleWriter & mWriter;
	ColorManager mColorManager;
	std::vector< ConsoleColor::Text> mTextColors;
	std::vector< ConsoleColor::Background> mBackgroundColors;
	std::vector< ConsoleColor::Text>::iterator mTextColorIt;
	std::vector< ConsoleColor::Background>::iterator mBackgroundColorIt;
	ConsoleColor::Text & mCurrentTextColor;
	ConsoleColor::Background & mCurrentBackgroundColor;
	bool mheadacheMode{ false };
	
public:
	View();
	void showCurrent(CellMatrix & currentCellMatrix);
	void toggleBackgroundColor();
	void changeTextColor();
	void headache();
	void toggleHeadache();
};


#endif // !_VIEW_H_
