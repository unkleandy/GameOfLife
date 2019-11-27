#pragma once
#include "./Console/ConsoleColor.h"
#include <thread>			// for timer
#include <chrono>			// for timer


class ColorManager

{

private:
	int time{1};
	std::vector< ConsoleColor::Text> mTextColors;
	std::vector< ConsoleColor::Background> mBackgroundColors;
	std::vector< ConsoleColor::Text>::iterator mTextColorIt;
	std::vector< ConsoleColor::Background>::iterator mBackgroundColorIt;
	ConsoleColor::Text mCurrentTextColor;
	ConsoleColor::Background mCurrentBackgroundColor;

public:
	ColorManager();
	~ColorManager();
	void changeTextColor();
	void changeBackgroundColor();
	void timer();
	void colorAnimate();
	ConsoleColor::Text getTextColor();
	ConsoleColor::Background getBackgroundColor();

};

