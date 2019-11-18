#include "ConsoleContext.h"



ConsoleContext::ConsoleContext()
	: ConsoleContext(120, 30, "", 0, 16, L"Consolas")
{
}

ConsoleContext::ConsoleContext(size_t w, size_t h, std::string const & t, int16_t fw, int16_t fh, std::wstring const & fn)
	: width{ w }, height{ h }, title(t), fontWidth{ fw }, fontHeight{ fh }, fontName(fn)
{
}

ConsoleContext::ConsoleContext(size_t w, size_t h, std::string const & t, int16_t fsize, std::wstring const & fn)
	: ConsoleContext(w, h, t, fsize, fsize, fn)
{
}

ConsoleContext::ConsoleContext(size_t size, std::string const & t, int16_t fsize, std::wstring const & fn)
	: ConsoleContext(size, size, t, fsize, fsize, fn)
{
}

ConsoleContext ConsoleContext::themeStandard()
{
	return ConsoleContext();
}

ConsoleContext ConsoleContext::themeCompact()
{
	return ConsoleContext(100, 100, "", 8, 8, L"Consolas");
}

ConsoleContext ConsoleContext::themePixelSquare(size_t w, size_t h, int16_t fSize, std::wstring const & fn)
{
	return ConsoleContext(w, h, "", fSize, fSize, fn);
}

ConsoleContext ConsoleContext::themeSquare(size_t screenSize, int16_t fSize, std::wstring const & fn)
{
	return themePixelSquare(screenSize, screenSize, fSize, fn);
}
