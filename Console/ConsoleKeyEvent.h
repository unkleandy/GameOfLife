#ifndef CONSOLE_KEY_EVENT
#define CONSOLE_KEY_EVENT


#define NOMINMAX
#include "Windows.h"

#include <string>


class ConsoleKeyEvent
{
	KEY_EVENT_RECORD mKeyEventRecord;

	friend class ConsoleKeyReader;
	ConsoleKeyEvent() = default;
	ConsoleKeyEvent(KEY_EVENT_RECORD keyEventRecord);

public:
	std::string toDebugString() const;
	// Existing key encoding format
	enum class KeyEncoding { 
			Ascii, 
			Unicode, 
			Virtual 
		};
	// Type of activated action
	enum class KeyState {
			KeyDown		= TRUE,
			KeyUp		= FALSE
		};
	// Special modifiers combination
	enum class KeyModifier {
			LeftAlt		= LEFT_ALT_PRESSED,
			RightAlt	= RIGHT_ALT_PRESSED,
			Alt			= LeftAlt | RightAlt,
			LectCtrl	= LEFT_CTRL_PRESSED,
			RightCtrl	= RIGHT_CTRL_PRESSED,
			Ctrl		= LectCtrl | RightCtrl,
			Shift		= SHIFT_PRESSED,
			Caps		= CAPSLOCK_ON,
			Num			= NUMLOCK_ON
		};

	// Return input key translate to ascii counterpart.
	char keyA() const;
	// Return input key translate to unicode counterpart.
	wchar_t keyU() const;
	// Return input key translate to virtual-key-code counterpart (Windows encoding).
	uint16_t keyV() const;
	// Return the number of occurence (repeated key).
	size_t occurrence() const;

	// Return true if the action was a key down.
	bool keyDown() const;
	// Return true if the action was a key up.
	bool keyUp() const;
	// Return true if action was keyAction.
	bool state(KeyState sate) const;
	// Return true if keyModifier was activated.
	bool modifier(KeyModifier keyModifier) const;
};

#endif // CONSOLE_KEY_EVENT
