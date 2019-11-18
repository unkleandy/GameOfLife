#include "ConsoleWriter.h"


#include "Console.h"


ConsoleWriter::ConsoleWriter(Console & console)
	: mConsole{ console } 
{
}

void ConsoleWriter::gotoxy(size_t x, size_t y)
{
	SetConsoleCursorPosition(mConsole.mHandleConsoleOutput, COORD{ static_cast<SHORT>(x), static_cast<SHORT>(y) });
}

void ConsoleWriter::setColor(ConsoleColor const & color)
{
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(mConsole.mHandleConsoleOutput, &screenInfo);
	SetConsoleTextAttribute(mConsole.mHandleConsoleOutput, color.color(screenInfo.wAttributes));
}

void ConsoleWriter::write(ConsoleImage const & image)
{
	WriteConsoleOutputA(mConsole.mHandleConsoleOutput, image.mBuffer.data(), mConsole.mBufferSize, COORD{0, 0}, &mConsole.mWindowRect);
}

void ConsoleWriter::write(std::string const & imageName)
{
	write(image(imageName));
}

ConsoleImage& ConsoleWriter::createImage(std::string const & name, char outputChar, ConsoleColor color)
{
	return mImages.insert(std::make_pair(name, ConsoleImage(*this, outputChar, color))).first->second;
}

void ConsoleWriter::removeImage(std::string const & imageName)
{
	auto it{ mImages.find(imageName) };
	if (it != mImages.end()) {
		mImages.erase(it);
	}
}

ConsoleImage& ConsoleWriter::image(std::string const & name)
{
	return mImages.at(name);
}

void ConsoleWriter::randomize()
{
	ConsoleImage im(*this);
	im.randomize();
	write(im);
}

void ConsoleWriter::calib()
{
	ConsoleImage im(*this);
	im.calib();
	write(im);
}

size_t ConsoleWriter::width() const
{
	return mConsole.mWidth;
}

size_t ConsoleWriter::height() const
{
	return mConsole.mHeight;
}
