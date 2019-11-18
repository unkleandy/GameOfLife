#include "ConsoleKeyFilterModifiers.h"


ConsoleKeyFilterModifiers::ConsoleKeyFilterModifiers() 
	: ConsoleKeyFilterAny<>() 
{
	mFilteredKeys[VK_CAPITAL] = true;		// 0x14		20
	mFilteredKeys[VK_NUMLOCK] = true;		// 0x90		144
	mFilteredKeys[VK_SCROLL] = true;		// 0x91		145
	mFilteredKeys[VK_SHIFT] = true;			// 0x10		16
	mFilteredKeys[VK_CONTROL] = true;		// 0x11		17
	mFilteredKeys[VK_MENU] = true;			// 0x12		19		ALT 
}

