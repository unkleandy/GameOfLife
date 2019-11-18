#include "Controler.h"
#include <random>			// for srand
#include <ctime>			// for srand

// constructor
Controller::Controller(Model & m, View & v)		:mModel{ m }, mView{ v }, mQuit{}	{}


Controller::~Controller()
{
}


int main() {
	srand(unsigned int(time(nullptr)));
	Model m;
	View v;
	Controller(m, v);

	return 0;
}

//
//class Controller
//{
//private:
//	Model model;
//	View view;
//
//public:
//	Controller(Model &, View &);
//	~Controller();
//	void run();
//};
