#ifndef CONSOLE_KEY_FILTER_H
#define CONSOLE_KEY_FILTER_H


#include "ConsoleKeyEvent.h"


class ConsoleKeyFilter
{
public:
	virtual bool isFiltered(ConsoleKeyEvent const & consoleKeyEvent) const = 0;
};


#endif // CONSOLE_KEY_FILTER_H
