#include "ConsoleImage.h"


#include "ConsoleWriter.h"
#include "Console.h"
#include <algorithm>
#include <cmath>


using namespace std;


ConsoleImage::ConsoleImage(ConsoleWriter & consoleWriter, char outputChar, ConsoleColor color)
	: mConsoleWriter{ consoleWriter },
	mBuffer(mConsoleWriter.mConsole.mBufferLinearSize)
{
	if (mConsoleWriter.mConsole.mBufferLinearSize == 0) {
		throw std::invalid_argument("Invalid argument in ConsoleImage::ConsoleImage : console must be initialized.");
	}
	fill(outputChar, color);
}

ConsoleImage & ConsoleImage::operator=(ConsoleImage const & im)
{
	mBuffer = im.mBuffer;

	return *this;
}

char ConsoleImage::character(int x, int y) const
{
	return get(x, y)->Char.AsciiChar;
}

ConsoleColor ConsoleImage::color(int x, int y) const
{
	return ConsoleColor(*get(x, y));
}

std::pair<char, ConsoleColor> ConsoleImage::pixel(int x, int y) const
{
	CHAR_INFO * pix{ get(x, y) };
	return std::make_pair(pix->Char.AsciiChar, ConsoleColor(*pix));
}

void ConsoleImage::fill(char outputChar, ConsoleColor color)
{
	CHAR_INFO charInfo;
	charInfo.Char.AsciiChar = outputChar;
	charInfo.Attributes = color.color();
	std::fill(mBuffer.begin(), mBuffer.end(), charInfo);
}

void ConsoleImage::fill(int x1, int y1, int width, int height, char outputChar, ConsoleColor color)
{
	if (width == 0 || height == 0) return;
	//assert((x1 + width - 1 < (int)mConsoleWriter.mConsole.mWidth) && (y1 + height - 1 < (int)mConsoleWriter.mConsole.mHeight));

	CHAR_INFO pix{ charInfo(outputChar, color) };

	CHAR_INFO * startX{ get(x1, y1) };
	CHAR_INFO * endX{ startX + width };
	CHAR_INFO * endY{ startX + height * mConsoleWriter.mConsole.mWidth };
	CHAR_INFO * cur{ startX };
	int stepY{ (int)mConsoleWriter.mConsole.mWidth - width };
	while (cur < endY) {
		while (cur < endX) {
			*cur++ = pix;
		}
		cur += stepY;
		endX += (int)mConsoleWriter.mConsole.mWidth;
	}
}

void ConsoleImage::fill(double x1, double y1, double width, double height, char outputChar, ConsoleColor color)
{
	fill(round(x1), round(y1), round(width), round(height), outputChar, color);
}

void ConsoleImage::drawPoint(int x, int y, char outputChar, ConsoleColor color)
{
	//assert(x < (int)mConsoleWriter.mConsole.mWidth && y < (int)mConsoleWriter.mConsole.mHeight);

	CHAR_INFO * pix{ get(x, y) };
	pix->Char.AsciiChar = outputChar;
	pix->Attributes = color.color();
}

void ConsoleImage::drawPoint(double x, double y, char outputChar, ConsoleColor color)
{
	drawPoint(round(x), round(y), outputChar, color);
}

void ConsoleImage::drawPoint(int x, int y, size_t size, char outputChar, ConsoleColor color)
{
	int halfSize{ (int)size / 2 };
	for (int i{ x - halfSize }; i < x + halfSize; ++i) {
		for (int j{ y - halfSize }; j < y + halfSize; ++j) {
			drawPoint(i, j, outputChar, color);
		}
	}
}

void ConsoleImage::drawPoint(double x, double y, size_t size, char outputChar, ConsoleColor color)
{
	double halfSize{ (double)size / 2 };
	for (double i{ x - halfSize }; i < x + halfSize; ++i) {
		for (double j{ y - halfSize }; j < y + halfSize; ++j) {
			drawPoint(i, j, outputChar, color);
		}
	}
}

void ConsoleImage::drawLine(int x1, int y1, int x2, int y2, char outputChar, ConsoleColor color)
{
	drawLine(x1, y1, x2, y2, charInfo(outputChar, color));
}

void ConsoleImage::drawLine(double x1, double y1, double x2, double y2, char outputChar, ConsoleColor color)
{
	drawLine(x1, y1, x2, y2, charInfo(outputChar, color));
}

void ConsoleImage::drawRect(int x1, int y1, int width, int height, char outputChar, ConsoleColor color)
{
	drawRect(x1, y1, width, height, charInfo(outputChar, color));
}

void ConsoleImage::drawRect(double x1, double y1, double width, double height, char outputChar, ConsoleColor color)
{
	drawRect(x1, y1, width, height, charInfo(outputChar, color));
}

void ConsoleImage::drawRect(int x1, int y1, int width, int height, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor)
{
	drawRect(x1, y1, width, height, borderOutputChar, borderColor);
	fill(x1 + 1, y1 + 1, std::max(static_cast<int>(0), width - 2), std::max(static_cast<int>(0), height - 2), fillOutputChar, fillColor);
}

void ConsoleImage::drawRect(double x1, double y1, double width, double height, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor)
{
	drawRect(x1, y1, width, height, borderOutputChar, borderColor);
	fill(x1 + 1, y1 + 1, std::max(0.0, width - 2), std::max(0.0, height - 2), fillOutputChar, fillColor);
}

void ConsoleImage::drawCircle(int x, int y, int radius, char outputChar, ConsoleColor color)
{
	drawCircle(x, y, radius, charInfo(outputChar, color));
}

void ConsoleImage::drawText(int x, int y, std::string const & text, ConsoleColor color, bool horizontal)
{
	int step{ 0 };
	if (horizontal) {
		//assert(x + text.size() <= (int)mConsoleWriter.mConsole.mWidth && y <= (int)mConsoleWriter.mConsole.mHeight);
		step = 1;
	} else {
		//assert(x < (int)mConsoleWriter.mConsole.mWidth && y + text.size() < (int)mConsoleWriter.mConsole.mHeight);
		step = (int)mConsoleWriter.mConsole.mWidth;
	}

	CHAR_INFO pixToDraw{ charInfo(' ', color) };
	CHAR_INFO * pix{ get(x, y) };
	for (auto charToDraw : text) {
		pixToDraw.Char.AsciiChar = charToDraw;
		*pix = pixToDraw;
		pix += step;
	}
}

void ConsoleImage::drawCenteredText(int pos, std::string const & text, ConsoleColor color, bool horizontal)
{
	if (horizontal) {
		drawText((int)(mConsoleWriter.mConsole.mWidth - text.length()) / 2, pos, text, color, true);
	} else {
		drawText(pos, (int)(mConsoleWriter.mConsole.mHeight - text.length()) / 2, text, color, false);
	}
}

void ConsoleImage::drawCenteredTextBox(int height, std::string const & text, ConsoleColor textColor, int horSpacer, int verSpacer, char borderOutputChar, ConsoleColor borderColor, char fillOutputChar, ConsoleColor fillColor)
{
	int boxWidth{ (int)text.length() + 2 * horSpacer };
	int boxHeight{ 1 + 2 * verSpacer };
	int boxLeft{ (int)(mConsoleWriter.mConsole.mWidth - boxWidth) / 2 };
	int boxTop{ height - verSpacer };
	int textLeft{ (int)(mConsoleWriter.mConsole.mWidth - text.length()) / 2 };

	drawRect(boxLeft, boxTop, boxWidth, boxHeight, borderOutputChar, borderColor, fillOutputChar, fillColor);
	drawText(textLeft, height, text, textColor, true);
}

void ConsoleImage::randomize()
{
	for (auto & pix : mBuffer) {
		pix.Char.AsciiChar = rand() % 26 + 'A';//uint8_t(219);
		pix.Attributes = (rand() % 7 + 7) | (rand() % 7 << 4);
	}
}

void ConsoleImage::calib()
{
	std::string calibText;
	calibText.resize(mConsoleWriter.mConsole.mWidth);
	int i{ 0 };
	for (auto & c : calibText) {
		c = i + '0';
		i = (i + 1) % 10;
	}
	for (int j{ 0 }; j < (int)mConsoleWriter.mConsole.mHeight; ++j) {
		drawText(0, j, calibText, ConsoleColor(static_cast<ConsoleColor::Text>(j % 7 + 8), static_cast<ConsoleColor::Background>(j % 7 + 0)), true);
	}
}

int ConsoleImage::width() const
{
	return (int)mConsoleWriter.width();
}

int ConsoleImage::height() const
{
	return (int)mConsoleWriter.height();
}

//template <> exception_management
#define WHEN_OUT_OF_RANGE_STILL_NEED_FOR_SPEED

CHAR_INFO * ConsoleImage::get(int x, int y) const
{
#if defined WHEN_OUT_OF_RANGE_GO_TO_NEAREST
	x = std::clamp(x, 0, (int)mConsoleWriter.mConsole.mWidth);
	y = std::clamp(y, 0, (int)mConsoleWriter.mConsole.mHeight);
	//if (x < 0) x = 0;
	//if (y < 0) y = 0;
	//if (x >= (int)mConsoleWriter.mConsole.mWidth) x = (int)mConsoleWriter.mConsole.mWidth - 1;
	//if (y >= (int)mConsoleWriter.mConsole.mHeight) y = (int)mConsoleWriter.mConsole.mHeight - 1;
#elif defined WHEN_OUT_OF_RANGE_ASSERT
	assert(x < mConsoleWriter.mConsole.mWidth && y < mConsoleWriter.mConsole.mHeight);
#elif defined WHEN_OUT_OF_RANGE_THROW
	if (x >= mConsoleWriter.mConsole.mWidth || y >= mConsoleWriter.mConsole.mHeight) {
		throw std::out_of_range("Invalid argument in ConsoleImage::get : x or y are out of range.");
	}
#elif defined WHEN_OUT_OF_RANGE_STILL_NEED_FOR_SPEED
	// do nothing => go for it => crash, crash!
#endif

	return const_cast<CHAR_INFO*>(mBuffer.data()) + y * mConsoleWriter.mConsole.mWidth + x;
}

CHAR_INFO ConsoleImage::charInfo(char outChar, ConsoleColor color)
{
	CHAR_INFO charInfo;
	charInfo.Char.AsciiChar = outChar;
	charInfo.Attributes = color.color();

	return charInfo;
}

void ConsoleImage::drawPoint(int x, int y, CHAR_INFO const & pix)
{
	*get(x, y) = pix;
}

void ConsoleImage::drawPoint(double x, double y, CHAR_INFO const & pix)
{
	drawPoint(round(x), round(y), pix);
}

void ConsoleImage::drawLine(int x1, int y1, int x2, int y2, CHAR_INFO const & pix)
{
	//assert(x1 < mConsoleWriter.mConsole.mWidth && y1 < mConsoleWriter.mConsole.mHeight && x2 < mConsoleWriter.mConsole.mWidth && y2 < mConsoleWriter.mConsole.mHeight);

	int deltaX{ static_cast<int>(x2 - x1) };
	int deltaY{ static_cast<int>(y2 - y1) };
	double length{ static_cast<double>(std::max(std::abs(deltaX), std::abs(deltaY))) };
	if (length == 0.0) return;

	double incX{ deltaX / length };
	double incY{ deltaY / length };
	for (double i{ static_cast<double>(x1) }, j{ static_cast<double>(y1) }, k{ 0.0 }; k <= length; i += incX, j += incY, k += 1.0) {
		drawPoint(static_cast<int>(std::round(i)), static_cast<int>(std::round(j)), pix);
	}
}

void ConsoleImage::drawLine(double x1, double y1, double x2, double y2, CHAR_INFO const & pix)
{
	//assert(x1 < mConsoleWriter.mConsole.mWidth && y1 < mConsoleWriter.mConsole.mHeight && x2 < mConsoleWriter.mConsole.mWidth && y2 < mConsoleWriter.mConsole.mHeight);

	double deltaX{ x2 - x1 };
	double deltaY{ y2 - y1 };
	double length{ std::max(std::abs(deltaX), std::abs(deltaY)) };
	if (length == 0.0) return;

	double incX{ deltaX / length };
	double incY{ deltaY / length };
	for (double i{ x1 }, j{ y1 }, k{ 0.0 }; k <= length; i += incX, j += incY, k += 1.0) {
		drawPoint(round(i), round(j), pix);
	}
}

void ConsoleImage::drawRect(int x1, int y1, int width, int height, CHAR_INFO const & pix)
{
	//assert((x1 + width <= mConsoleWriter.mConsole.mWidth) && (y1 + height <= mConsoleWriter.mConsole.mHeight));
	if (width == 0 || height == 0) return;

	int x2 = x1 + width - 1, y2 = y1 + height - 1;
	drawLine(x1, y1, x2, y1, pix);			// top
	drawLine(x1, y2, x2, y2, pix);			// bottom
	drawLine(x1, y1 + 1, x1, y2 - 1, pix);	// left
	drawLine(x2, y1 + 1, x2, y2 - 1, pix);	// right
}

void ConsoleImage::drawRect(double x1, double y1, double width, double height, CHAR_INFO const & pix)
{
	//assert((x1 + width <= mConsoleWriter.mConsole.mWidth) && (y1 + height <= mConsoleWriter.mConsole.mHeight));
	if (width == 0 || height == 0) return;

	double x2 = x1 + width, y2 = y1 + height;  /// ??? on enleve le -1 -> à confirmer
	drawLine(x1, y1, x2, y1, pix);			// top
	drawLine(x1, y2, x2, y2, pix);			// bottom
	drawLine(x1, y1 + 1, x1, y2 - 1, pix);	// left
	drawLine(x2, y1 + 1, x2, y2 - 1, pix);	// right
}

void ConsoleImage::drawCircle(int x, int y, int radius, CHAR_INFO const & pix)
{
	double curTheta{};
	double deltaTheta{ std::asin(1.0 / radius) };
	double lastTheta{ 6.283185307179586476925286766559 };
	while (curTheta <= lastTheta) {
		drawPoint(x + radius * std::cos(curTheta), y + radius * std::sin(curTheta), pix);
		curTheta += deltaTheta;
	}
}

int ConsoleImage::round(double value) const
{
	return static_cast<int>(std::round(value));
}
