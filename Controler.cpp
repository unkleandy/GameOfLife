#include "Controler.h"
#include <random>			// for srand
#include <ctime>			// for srand
#include <string>			// for tesing rle path in MAIN
#include <iostream>			// for tesing evolution
#include <conio.h>			// for getch
#include "rleUtil.h"
#include "CellMatrix.h"

// constructor
Controller::Controller(Model & m, View & v)		:mModel{ m }, mView{ v }, mQuit{}	{}



Controller::~Controller()
{
}



void Controller::run()
{
	std::string path{"./fichiers_test_rle/honeycomb_synth.rle"};
	//std::string path{"..GoL\\fichiers_test_rle\\validation_invalid_header_2.rle"};
	RleUtil rle(path);
	//clock_t time{ clock() };

	mModel.gol().importAndCenterCellmatrix(rle.cellmatrix());
	mModel.gol().cellmatrix().show();
	_getch();
	while (true) {
		system("cls");
		mModel.gol().cellmatrix().show();
		mModel.gol().evolveMatrix();
		_getch();
	}
}


void Controller::initaliseConsoleContext()
{}

int main() {
	srand(unsigned int(time(nullptr)));
	Model m;
	View v;
	Controller c(m, v);
	c.run();


	return 0;
}
