#include "Controler.h"
#include <random>			// for srand
#include <ctime>			// for srand
#include "rleUtil.h"
#include "CellMatrix.h"

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
	std::string txt = "x = 76, y = 53, rule = B3/S23 ";
	std::string matrix = "\nobo$b2o$bo17$20bo$21b2o$20b2o5$51b2o$52bo$52bobo$42bo10b2o$40b3o$39bo$\n39b2o$24b2o48b2o$25bo48b2o$25bob2o$26bo2bo23bo$27b2o24bo$42b2o9b3o$42b\n2o11bo4$51bo3b2o$50bobo3bo$49bobo3bo$45b2obobo3bo$45b2obo2b4obo5b2o$\n49bobo3bobo5bo$45b2ob2o2bo2bobo2b3o$46bobo2b2o3bo3bo$34b2o10bobo$34b2o\n11bo!";
	RleUtil rle;
	rle.setDimRuleFromString(txt);
	rle.setMatrixFromString(matrix);
	mModel.gol().importAndCenterCellmatrix(rle.cellmatrix());
	mModel.gol().cellmatrix().show();

}

Controller::~Controller()
{
}

//
//int main() {
//	srand(unsigned int(time(nullptr)));
//	Model m;
//	View v;
//	Controller c(m, v);
//	c.run();
//
//	return 0;
//}
