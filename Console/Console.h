#ifndef CONSOLE_H
#define CONSOLE_H


#define NOMINMAX
#include <Windows.h>
#include <cstdint>
#include <exception>

#include "ConsoleKeyReader.h"
#include "ConsoleWriter.h"


class ConsoleContext;


class Console
{
	static ConsoleContext mContext;
	Console(ConsoleContext const & context);

public:
	static void defineContext(ConsoleContext const & context);
	static Console& getInstance();

	static const size_t MinScreenWidth{ 20 };
	static const size_t MaxScreenWidth{ 600 };
	static const size_t MinScreenHeight{ 20 };
	static const size_t MaxScreenHeight{ 400 };
	static const uint16_t MinFontSize{ 2 };
	static const uint16_t MaxFontSize{ 36 };

	ConsoleKeyReader& keyReader();
	ConsoleWriter& writer();

	size_t width() const;
	size_t height() const;
	
	class ConsoleExcept : public std::exception {};
	class NoOutputConsole : public ConsoleExcept {};
	class NoInputConsole : public ConsoleExcept {};
	class NoTitleConsole : public ConsoleExcept {};

private:
	HANDLE mHandleConsoleOutput;
	HANDLE mHandleConsoleInput;
	ConsoleKeyReader mConsoleKeyReader;
	ConsoleWriter mConsoleWriter;
	size_t mWidth, mHeight, mBufferLinearSize;
	COORD mBufferSize;
	SMALL_RECT mWindowRect;

	friend class ConsoleKeyReader;
	friend class ConsoleWriter;
	friend class ConsoleImage;
};





#endif // CONSOLE_H