#include "ConsoleKeyReader.h"


#include "Console.h"
#include <vector>


ConsoleKeyReader::ConsoleKeyReader(Console & consol) 
	: mConsole{ consol } 
{
}

void ConsoleKeyReader::read(KeyEvents & keyEvents, bool append)
{
	//static const size_t inputRecordsSize{ 1024 };
	//static INPUT_RECORD inputRecords[inputRecordsSize];
	DWORD numberOfEvents;

	if (!append) {
		keyEvents.clear();
	}
	GetNumberOfConsoleInputEvents(mConsole.mHandleConsoleInput, &numberOfEvents);
	if (numberOfEvents > 0) {
		std::vector<INPUT_RECORD> inputRecords(numberOfEvents);
		if (ReadConsoleInput(mConsole.mHandleConsoleInput, inputRecords.data(), numberOfEvents, &numberOfEvents)) {
			for (size_t i{ 0 }; i < numberOfEvents; ++i) {
				switch (inputRecords[i].EventType) {
					case KEY_EVENT:
						ConsoleKeyEvent keyEvent(inputRecords[i].Event.KeyEvent);
						if (!isFiltered(keyEvent)) keyEvents.push_back(keyEvent);
						break;
					case MOUSE_EVENT:
						// disregard
						break;
					case WINDOW_BUFFER_SIZE_EVENT:
						// disregard
						break;
					case FOCUS_EVENT:
						// disregard
						break;
					case MENU_EVENT:
						// disregard
						break;
				}
			}
		} else {
			throw Console::NoInputConsole();
		}
	}
}

void ConsoleKeyReader::installFilter(ConsoleKeyFilter * filter)
{
	if (filter) {
		mFilters.emplace_back(filter);
	}
}

void ConsoleKeyReader::installFilter(std::unique_ptr<ConsoleKeyFilter> & filter)
{
	if (filter) {
		mFilters.push_back(std::move(filter));
	}
}
void ConsoleKeyReader::clearFilters() 
{ 
	mFilters.clear();
}

bool ConsoleKeyReader::isFiltered(ConsoleKeyEvent const & event) const 
{
	for (auto it{ mFilters.begin() }; it != mFilters.end(); ++it) {
		if ((*it)->isFiltered(event)) {
			return true;
		}
	}
	return false;
}
