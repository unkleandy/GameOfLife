#include "Console.h"
#include "ConsoleContext.h"
#include "ConsoleColor.h"
#include "ConsoleKeyReader.h"
#include "ConsoleKeyFilterDown.h"
#include "ConsoleKeyFilterModifiers.h"


#include <iostream>

int main()
{
	ConsoleContext context(50, 50, "Yo man", 10, L"Consolas");
	Console::defineContext(context);

	ConsoleWriter & writer{ Console::getInstance().writer() };
	ConsoleKeyReader & reader{ Console::getInstance().keyReader() };
	reader.installFilter(new ConsoleKeyFilterDown);
	reader.installFilter(new ConsoleKeyFilterModifiers);

	ConsoleImage &monImage{ writer.createImage("output") };
	monImage.drawLine(10, 10, 40, 35, char(219), ConsoleColor::tR + ConsoleColor::by);

	ConsoleKeyReader::KeyEvents events;
	while (true) {
		reader.read(events);

		if (events.size() == 0) {} 
		else {
			switch(events.front().keyA())
			{
				case 'z':
						writer.write(monImage);
						break;
				case 'a':
						writer.randomize();
						break;
			}
		}
	}

	return 0;
}