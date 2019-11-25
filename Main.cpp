#include "Main.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "./Console/Console.h"
#include "./Console/ConsoleContext.h"
#include "./Console/ConsoleColor.h"
#include "./Console/ConsoleKeyReader.h"
#include "./Console/ConsoleKeyFilterDown.h"
#include "./Console/ConsoleKeyFilterModifiers.h"

#include <time.h>


void initaliseConsoleContext(int dimX, int dimY)
{
	ConsoleContext context(dimX, dimY, "Game Of Life", 5, L"Consolas");
	Console::defineContext(context);
}

int main() {

	int dimX{ 150 };
	int dimY{ 150 };
	initaliseConsoleContext(dimX, dimY);
	srand(unsigned int(time(nullptr)));
	Model m(dimX, dimY);
	View v;
	Controller c(m, v);

	c.run();

	return 0;
}
