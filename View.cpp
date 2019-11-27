#include "View.h"



View::View()
	:
	mWriter{ Console::getInstance().writer() },
	mColorManager{},
	mTextColors{ ConsoleColor::Text::BrightWhite, 
				ConsoleColor::Text::BrightRed, 
				ConsoleColor::Text::BrightGreen, 
				ConsoleColor::Text::BrightBlue,
				ConsoleColor::Text::BrightYellow, 
				ConsoleColor::Text::BrightMagenta, 
				ConsoleColor::Text::BrightCyan 
	},
	mBackgroundColors{ ConsoleColor::Background::Black,
				ConsoleColor::Background::White, 
				ConsoleColor::Background::Red, 
				ConsoleColor::Background::Green,
				ConsoleColor::Background::Blue,
				ConsoleColor::Background::Yellow, 
				ConsoleColor::Background::Magenta,
				ConsoleColor::Background::Cyan, 
	},
	mTextColorIt{ mTextColors.begin() },
	mCurrentTextColor{ * mTextColors.begin() },
	mBackgroundColorIt{ mBackgroundColors.begin() },
	mCurrentBackgroundColor{ * mBackgroundColors.begin() }
{
	mWriter.createImage("output") ; 
	
}


void View::showCurrent(CellMatrix & currentCellMatrix) 
{
	//mWriter.image("output").fill(cellInactive, mCurrentBackgroundColor);
	char c;
	itCM currentCell{ currentCellMatrix.matrix().begin() };
	for (int posY{}; posY < currentCellMatrix.y(); ++posY)
	{
		for (int posX{ 0 }; posX < currentCellMatrix.x(); ++posX)
		{
			c = (*currentCell).state() ? cellActive : cellInactive;
			if (c == cellInactive) {
				mWriter.image("output").drawPoint(posX, posY, c, mCurrentBackgroundColor);
			}
			else {
				mWriter.image("output").drawPoint(posX, posY, c, mCurrentTextColor);
			}
			++currentCell;
		}
	}
	mWriter.write(mWriter.image("output"));
}

void View::changeTextColor()
{

	++mTextColorIt;
	++mBackgroundColorIt;
	if (mBackgroundColorIt == mBackgroundColors.end())
	{
		mTextColorIt = mTextColors.begin();
		mBackgroundColorIt = mBackgroundColors.begin();
	}
	mCurrentTextColor = *mTextColorIt;

}

void View::headache(CellMatrix & currentCellMatrix)
{
	mCurrentBackgroundColor = mColorManager.getBackgroundColor();
	mCurrentTextColor = mColorManager.getTextColor();
	showCurrent(currentCellMatrix);
	mColorManager.colorAnimate();
}

void View::toggleBackgroundColor()
{
	if (mCurrentBackgroundColor == ConsoleColor::Background::Black)
		{ mCurrentBackgroundColor = *(mBackgroundColorIt); }
	else { mCurrentBackgroundColor = ConsoleColor::Background::Black; }
}
