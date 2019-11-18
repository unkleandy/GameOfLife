#include "ConsoleKeyFilterDown.h"


bool ConsoleKeyFilterDown::isFiltered(ConsoleKeyEvent const & consoleKeyEvent) const 
{ 
	return consoleKeyEvent.keyDown(); 
}