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

	initaliseConsoleContext(dim, dim);
	srand(unsigned int(time(nullptr)));
	Model m(dim, dim);
	View v;
	Controller c(m, v);

	c.run();

	return 0;
}
