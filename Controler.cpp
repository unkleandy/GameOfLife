#include "Controler.h"
#include <random>			// for srand
#include <ctime>			// for srand

// constructor
Controller::Controller(Model & m, View & v)		:mModel{ m }, mView{ v }, mQuit{}	{}

/*
int x{};
	int y{};
	view.UI_showMatrixSizeMenu(x, y);
	

	model.setCellMatrix(x, y);
	char reponse{};
	bool quit{};

	while (!quit)
	{
		model.update();
		view.showCurrent(model);
		reponse = getUpperChar();

		if (reponse == 'R')
		{
			model.reinitialise();
		}
		else
		{
			model.nextrule();
		}

		if (reponse == 'Q')
		{
			view.menuQuit();
		}
	}
}
*/


void Controller::run()
{
	mModel.setCellMatrix(40, 20);
	mModel.cellmatrix().randomizeMatrix();

}

Controller::~Controller()
{
}


int main() {
	srand(unsigned int(time(nullptr)));
	Model m;
	View v;
	Controller c(m, v);
	c.run();

	return 0;
}
