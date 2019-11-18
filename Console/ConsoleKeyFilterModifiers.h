#ifndef CONSOLE_KEY_FILTER_MODIFIERS_H
#define CONSOLE_KEY_FILTER_MODIFIERS_H


#include "ConsoleKeyFilterAny.h"


// These filters are for one key filtering. If you need to filter a 
// combination of n specific keys, you must not include the first key 
// in any of the following filters.


class ConsoleKeyFilterModifiers : public ConsoleKeyFilterAny<>
{
public:
	ConsoleKeyFilterModifiers();
};

#endif // CONSOLE_KEY_FILTER_MODIFIERS_H
