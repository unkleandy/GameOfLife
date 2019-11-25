#include "View.h"


View::View()
	:
	mWriter{ Console::getInstance().writer() },
	mTextColors{ ConsoleColor::Text::BrightWhite, 
				ConsoleColor::Text::BrightRed, 
				ConsoleColor::Text::BrightGreen, 
				ConsoleColor::Text::BrightBlue,
				ConsoleColor::Text::BrightYellow, 
				ConsoleColor::Text::BrightMagenta, 
				ConsoleColor::Text::BrightCyan 
	},
	mBackgroundColors{ ConsoleColor::Background::White, 
				ConsoleColor::Background::Red, 
				ConsoleColor::Background::Green,
				ConsoleColor::Background::Blue,
				ConsoleColor::Background::Yellow, 
				ConsoleColor::Background::Magenta,
				ConsoleColor::Background::Cyan, 
				ConsoleColor::Background::Black
	},
	mTextColorIt{ mTextColors.begin() },
	mCurrentTextColor{0},
	mCurrentBackgroundColor{ ConsoleColor::Background::Black }
{}


void View::showCurrent(CellMatrix & currentCellMatrix) 
{

	ConsoleImage & matrixImage{ Console::getInstance().writer().image("output") };
	
	char c;
	itCM currentCell{ currentCellMatrix.matrix().begin() };
	for (int posY{}; posY < currentCellMatrix.y(); ++posY)
	{
		for (int posX{ 0 }; posX < currentCellMatrix.x(); ++posX)
		{
			c = (*currentCell).state() ? Cell::active : Cell::inactive;
			matrixImage.drawPoint(posX, posY, ((*currentCell).state() ? Cell::active : Cell::inactive), mCurrentTextColor);
			++currentCell;
		}
		
	}
}

void changeTextColor() 
{
	////if(mCurrentTextColor<ConsoleColor::Opaque count)
	////	https://stackoverflow.com/questions/14989274/is-it-possible-to-determine-the-number-of-elements-of-a-c-enum-class
	//++mTextColorIt;
	//mCurrentTextColor = *mTextColorIt;
}

void toggleBackgroundColor()
{
	//if (mCurrentBackgroundColor != ConsoleColor::Background::Black)
	//{
	////	{ mCurrentBackgroundColor = (ConsoleColor::Background) mCurrentTextColor; }
	//	{ mCurrentBackgroundColor = *(mBackgroundColors.begin() + (std::distance(mTextColors.begin(), mTextColorIt)); }
	//}
	//else { mCurrentBackgroundColor = ConsoleColor::Background::Black; }
}