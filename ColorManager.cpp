#include "ColorManager.h"



ColorManager::ColorManager()
	: mTextColors{ ConsoleColor::Text::BrightWhite,
				ConsoleColor::Text::BrightGreen,
				ConsoleColor::Text::BrightCyan,
				ConsoleColor::Text::BrightCyan,
				ConsoleColor::Text::BrightRed,
	},
	mBackgroundColors{ ConsoleColor::Background::Black,
				ConsoleColor::Background::BrightYellow,
				ConsoleColor::Background::BrightGreen,
				ConsoleColor::Background::Magenta,
				ConsoleColor::Background::BrightBlue,
	},
	mTextColorIt{ mTextColors.begin() },
	mBackgroundColorIt{ mBackgroundColors.begin() },
	mCurrentTextColor{ *mTextColors.begin() },
	mCurrentBackgroundColor{ *mBackgroundColors.begin() }
{
	
}


ColorManager::~ColorManager()
{
}

void ColorManager::changeTextColor()
{
	++mTextColorIt;
	mCurrentTextColor = *mTextColorIt;
}

void ColorManager::changeBackgroundColor()
{
	++mBackgroundColorIt;
	mCurrentBackgroundColor = *mBackgroundColorIt;
}

void ColorManager::timer()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		++time;
	}
}

void ColorManager::colorAnimate()
{
	// partir le timer
	timer();

	// change les couleurs 
	if (time % 4 == 0) {

		changeTextColor();
		changeBackgroundColor();
	}
}

ConsoleColor::Text ColorManager::getTextColor()
{
	return *mTextColors.begin();
}

ConsoleColor::Background ColorManager::getBackgroundColor()
{
	return *mBackgroundColors.begin();
}
