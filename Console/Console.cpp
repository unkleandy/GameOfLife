#include "Console.h"


#include "ConsoleContext.h"
#include <string>


using namespace std;


ConsoleContext Console::mContext(ConsoleContext::themeStandard());


Console::Console(ConsoleContext const & context)
	:	mHandleConsoleOutput{ GetStdHandle(STD_OUTPUT_HANDLE) },
		mHandleConsoleInput{ GetStdHandle(STD_INPUT_HANDLE) },
		mConsoleKeyReader(*this),
		mConsoleWriter(*this),
		mWidth{ std::clamp(context.width, MinScreenWidth, MaxScreenWidth) },
		mHeight{ std::clamp(context.height, MinScreenHeight, MaxScreenHeight) },
		mBufferLinearSize{ mWidth * mHeight },
		mBufferSize{ static_cast<int16_t>(mWidth), static_cast<int16_t>(mHeight) },
		mWindowRect{ 0, 0, static_cast<int16_t>(mWidth) - 1, static_cast<int16_t>(mHeight) - 1 }
{
	if (mHandleConsoleOutput == NULL) {
		throw NoOutputConsole();
	}
	if (mHandleConsoleInput == NULL) {
		throw NoInputConsole();
	}

	//system("mode con:");
	// Set console mode - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	//DWORD consoleMode;
	//GetConsoleMode(mHandleConsoleOutput, &consoleMode);
	//consoleMode |= ENABLE_ECHO_INPUT;
	//consoleMode |= ENABLE_EXTENDED_FLAGS;
	//consoleMode |= ENABLE_INSERT_MODE;
	//consoleMode |= ENABLE_LINE_INPUT;
	//consoleMode |= ENABLE_MOUSE_INPUT;
	//consoleMode |= ENABLE_PROCESSED_INPUT;
	//consoleMode |= ENABLE_QUICK_EDIT_MODE;
	//consoleMode |= ENABLE_WINDOW_INPUT;
	//consoleMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
	//consoleMode |= ENABLE_PROCESSED_OUTPUT;
	//consoleMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	////consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	////consoleMode &= DISABLE_NEWLINE_AUTO_RETURN;
	//SetConsoleMode(mHandleConsoleOutput, consoleMode);
	std::string systemMode("mode con: cols=" + to_string(mWidth) + " lines=" + to_string(mHeight)); // system("mode 120, 30");
	system(systemMode.c_str());

	// Setup history info  - - - - - - - - - - - - - - - - - - - - - - - - - - 
	//CONSOLE_HISTORY_INFO consoleHistoryInfo;
	//consoleHistoryInfo.cbSize = sizeof(CONSOLE_HISTORY_INFO);
	//consoleHistoryInfo.HistoryBufferSize = 0;
	//consoleHistoryInfo.NumberOfHistoryBuffers = 0;
	//consoleHistoryInfo.dwFlags = 0;
	//BOOL test = SetConsoleHistoryInfo(&consoleHistoryInfo);

	// Set font appearance - - - - - - - - - - - - - - - - - - - - - - - - - - 
	CONSOLE_FONT_INFOEX consoleFontInfoEx;
	consoleFontInfoEx.cbSize = sizeof(consoleFontInfoEx);
	consoleFontInfoEx.nFont = 0;
	consoleFontInfoEx.dwFontSize.X = std::clamp((SHORT)context.fontWidth, (SHORT)MinFontSize, (SHORT)MaxFontSize);
	consoleFontInfoEx.dwFontSize.Y = std::clamp((SHORT)context.fontHeight, (SHORT)MinFontSize, (SHORT)MaxFontSize);
	consoleFontInfoEx.FontFamily = FF_DONTCARE;
	consoleFontInfoEx.FontWeight = FW_NORMAL;
	wcscpy_s(consoleFontInfoEx.FaceName, context.fontName.c_str());
	SetCurrentConsoleFontEx(mHandleConsoleOutput, FALSE, &consoleFontInfoEx);

	// Set screen buffer and window size - - - - - - - - - - - - - - - - - - - 
	SetConsoleScreenBufferSize(mHandleConsoleOutput, mBufferSize);
	SetConsoleWindowInfo(mHandleConsoleOutput, TRUE, &mWindowRect);

	// Set window title - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	if (context.title.length() > 0) {
		if (!SetConsoleTitleA(context.title.c_str())) {
			throw NoTitleConsole();
		}
	}

	// Hide cursor - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mHandleConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(mHandleConsoleOutput, &cursorInfo);

	// Non resizable window - - - - - - - - - - - - - - - - - - - - - - - - - -
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

}

void Console::defineContext(ConsoleContext const & context)
{
	mContext = context;
}

Console & Console::getInstance()
{
	static Console console(mContext);
	return console;
}

ConsoleKeyReader& Console::keyReader() 
{ 
	return mConsoleKeyReader; 
}

ConsoleWriter & Console::writer()
{
	return mConsoleWriter;
}

size_t Console::width() const
{
	return mWidth;
}

size_t Console::height() const
{
	return mHeight;
}


