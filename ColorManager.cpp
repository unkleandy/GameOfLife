#include "ColorManager.h"



ColorManager::ColorManager()
	: mTextColors{ ConsoleColor::Text::BrightWhite,
				ConsoleColor::Text::BrightGreen,
				ConsoleColor::Text::BrightCyan,
				ConsoleColor::Text::BrightBlue,
				ConsoleColor::Text::BrightRed,
				ConsoleColor::Text::BrightMagenta,
	},
	mBackgroundColors{ ConsoleColor::Background::Black,
				ConsoleColor::Background::BrightYellow,
				ConsoleColor::Background::BrightMagenta,
				ConsoleColor::Background::BrightRed,
				ConsoleColor::Background::BrightBlue,
				ConsoleColor::Background::BrightGreen,
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
	if (mTextColorIt == mTextColors.end())
	{
		mTextColorIt = mTextColors.begin();
	}
	mCurrentTextColor = *mTextColorIt;
}

void ColorManager::changeBackgroundColor()
{
	++mBackgroundColorIt;
	if (mBackgroundColorIt == mBackgroundColors.end())
	{
		mBackgroundColorIt = mBackgroundColors.begin();
	}
	mCurrentBackgroundColor = *mBackgroundColorIt;
}

void ColorManager::colorAnimate()
{
	// partir le timer
	static int compteur;

	// change les couleurs 
	if (compteur % 4 == 0) {

		changeTextColor();
		changeBackgroundColor();
	}
	++compteur;
}

ConsoleColor::Text ColorManager::getTextColor()
{
	return mCurrentTextColor;
}

ConsoleColor::Background ColorManager::getBackgroundColor()
{
	return mCurrentBackgroundColor;
}
