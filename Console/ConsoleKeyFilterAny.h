#ifndef CONSOLE_KEY_FILTER_ANY_H
#define CONSOLE_KEY_FILTER_ANY_H


#include "ConsoleKeyFilter.h"
#include <array>


// These filters are for one key filtering. If you need to filter a 
// combination of n specific keys, you must not include the first key 
// in any of the following filters.


template <size_t LutSize = 0xFF, ConsoleKeyEvent::KeyEncoding keyEncoding = ConsoleKeyEvent::KeyEncoding::Virtual>
class ConsoleKeyFilterAny : public ConsoleKeyFilter
{
protected:
	std::array<bool, LutSize> mFilteredKeys;

public:
	ConsoleKeyFilterAny();

	bool isFiltered(ConsoleKeyEvent const & consoleKeyEvent) const;

	bool isSet(size_t index) const;
	void set(size_t index, bool value);
	void set(bool value);
};




template <size_t LutSize, ConsoleKeyEvent::KeyEncoding keyEncoding>
ConsoleKeyFilterAny<LutSize, keyEncoding>::ConsoleKeyFilterAny()
{
	set(false);
}

template <size_t LutSize, ConsoleKeyEvent::KeyEncoding keyEncoding>
inline bool ConsoleKeyFilterAny<LutSize, keyEncoding>::isFiltered(ConsoleKeyEvent const & consoleKeyEvent) const
{
	if constexpr (keyEncoding == ConsoleKeyEvent::KeyEncoding::Ascii) {
		return mFilteredKeys[consoleKeyEvent.keyA()];
	} else if constexpr (keyEncoding == ConsoleKeyEvent::KeyEncoding::Unicode) {
		return mFilteredKeys[consoleKeyEvent.keyU()];
	} else {
		return mFilteredKeys[consoleKeyEvent.keyV()];
	}
}

template <size_t LutSize, ConsoleKeyEvent::KeyEncoding keyEncoding>
inline bool ConsoleKeyFilterAny<LutSize, keyEncoding>::isSet(size_t index) const
{ 
	return mFilteredKeys[index]; 
}

template <size_t LutSize, ConsoleKeyEvent::KeyEncoding keyEncoding>
inline void ConsoleKeyFilterAny<LutSize, keyEncoding>::set(size_t index, bool value)
{ 
	mFilteredKeys[index] = value; 
}

template <size_t LutSize, ConsoleKeyEvent::KeyEncoding keyEncoding>
inline void ConsoleKeyFilterAny<LutSize, keyEncoding>::set(bool value)
{ 
	memset(mFilteredKeys.data(), value ? 0xFF : 0x00, sizeof(bool) * mFilteredKeys.size()); 
}





#endif // CONSOLE_KEY_FILTER_ANY_H
