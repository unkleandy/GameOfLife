#ifndef CONSOLE_KEY_READER
#define CONSOLE_KEY_READER


#include "ConsoleKeyFilter.h"
#include <list>


class Console;

class ConsoleKeyReader
{
public:
	using KeyEvents = std::list<ConsoleKeyEvent>;

	ConsoleKeyReader(Console & consol);

	void read(KeyEvents & keyEvents, bool append = false);

	void installFilter(ConsoleKeyFilter * filter);
	void installFilter(std::unique_ptr<ConsoleKeyFilter> & filter);
	void clearFilters();

private:
	Console & mConsole;
	std::list<std::unique_ptr<ConsoleKeyFilter>> mFilters;

	bool isFiltered(ConsoleKeyEvent const & event) const;
};

#endif // CONSOLE_KEY_READER
