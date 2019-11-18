#include "ConsoleKeyEvent.h"


#include <sstream>


ConsoleKeyEvent::ConsoleKeyEvent(KEY_EVENT_RECORD keyEventRecord) 
	: mKeyEventRecord{ keyEventRecord } 
{
}

std::string ConsoleKeyEvent::toDebugString() const 
{
	std::stringstream stream;
	stream << keyA() << " : " << keyU() << " : " << keyV()
		<< " {" << occurrence() << "} "
		<< "[" << (state(KeyState::KeyDown) ? "v" : "^") << "]"
		<< "alt[" << modifier(KeyModifier::LeftAlt) << "|" << modifier(KeyModifier::RightAlt) << "]"
		<< "ctrl[" << modifier(KeyModifier::LectCtrl) << "|" << modifier(KeyModifier::RightCtrl) << "]"
		<< "shift[" << modifier(KeyModifier::Shift) << "]"
		<< "caps[" << modifier(KeyModifier::Caps) << "]"
		<< "num[" << modifier(KeyModifier::Num) << "]";

	return stream.str();
}

char ConsoleKeyEvent::keyA() const 
{ 
	return mKeyEventRecord.uChar.AsciiChar; 
}
wchar_t ConsoleKeyEvent::keyU() const 
{ 
	return mKeyEventRecord.uChar.UnicodeChar; 
}
uint16_t ConsoleKeyEvent::keyV() const 
{ 
	return mKeyEventRecord.wVirtualKeyCode; 
}
size_t ConsoleKeyEvent::occurrence() const 
{ 
	return mKeyEventRecord.wRepeatCount; 
}
bool ConsoleKeyEvent::keyDown() const 
{ 
	return state(KeyState::KeyDown);
}
bool ConsoleKeyEvent::keyUp() const 
{ 
	return state(KeyState::KeyUp);
}
bool ConsoleKeyEvent::state(KeyState state) const
{ 
	return mKeyEventRecord.bKeyDown == static_cast<int>(state);
}
bool ConsoleKeyEvent::modifier(KeyModifier keyModifier) const 
{ 
	return mKeyEventRecord.dwControlKeyState & static_cast<int>(keyModifier); 
}
