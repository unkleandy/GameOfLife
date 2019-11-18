#include "ConsoleKeyFilterUp.h"



bool ConsoleKeyFilterUp::isFiltered(ConsoleKeyEvent const & consoleKeyEvent) const 
{ 
	return consoleKeyEvent.keyUp(); 
}