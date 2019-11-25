#include <random>			// for srand
#include <ctime>			// for srand
#include <string>			// for tesing rle path in MAIN
#include <iostream>			// for tesing evolution
#include <conio.h>			// for getch
#include <thread>			// for timer
#include <chrono>			// for timer

#include "Controller.h"
#include "rleUtil.h"
#include "CellMatrix.h"

#include "./Console/Console.h"
#include "./Console/ConsoleContext.h"

#include "./Console/ConsoleKeyReader.h"
#include "./Console/ConsoleKeyFilterDown.h"
#include "./Console/ConsoleKeyFilterModifiers.h"



// constructor
Controller::Controller(Model & m, View & v)		
	:
	mModel{ m }, 
	mView{ v }, 
	mModelAction(),
	mReader{ Console::getInstance().keyReader() }
{
}



Controller::~Controller()
{
}



void Controller::run()
{
	bool quit{};
	std::string path{"./fichiers_test_rle/snarkcatalystvariants.rle"};
	RleUtil rle(path);
	
	mReader.installFilter(new ConsoleKeyFilterDown);
	mReader.installFilter(new ConsoleKeyFilterModifiers);

	
	ConsoleKeyReader::KeyEvents events;

	mModel.gol().importAndCenterCellmatrix(rle.cellmatrix());
	
	while (!mQuit) 
	{
		//system("cls");
		
		mView.showCurrent(mModel.cellmatrix());
		mModel.gol().evolveMatrix();
		std::this_thread::sleep_for(std::chrono::milliseconds(mSpeed));

		if (events.size() != 0) 
		{
			mModelAction.doActionFromKey(events.front().keyA(), mModel, *this, mView);
		}
	}
}




void Controller::quit() { mQuit = true; }
void Controller::changeSpeed(unsigned int timesFaster) { mSpeed = (int) (500 / timesFaster); }



void Controller::keybinding()
{

	mModelAction.setAction((int)KeyBinding::Action_Quit, [](Model & model, Controller & controller, View & view)-> void { controller.quit(); });

	mModelAction.setAction((int)KeyBinding::Controler_Speed1, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(1); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed2, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(2); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed3, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(3); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed4, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(4); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed5, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(5); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed6, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(6); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed7, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(7); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed8, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(8); });
	mModelAction.setAction((int)KeyBinding::Controler_Speed9, [](Model & model, Controller & controller, View & view)-> void { controller.changeSpeed(9); });

	mModelAction.setAction((int)KeyBinding::Model_NextRule, [](Model & model, Controller & controller, View & view)-> void { model.nextRule(); });

	mModelAction.setAction((int)KeyBinding::Console_SwitchColor, [](Model & model, Controller & controller, View & view)-> void { view.changeTextColor(); });
	mModelAction.setAction((int)KeyBinding::Console_SwitchColor, [](Model & model, Controller & controller, View & view)-> void { view.toggleBackgroundColor(); });

	mModelAction.setAction((int)KeyBinding::Model_Random01, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.01); });
	mModelAction.setAction((int)KeyBinding::Model_Random05, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.05); });
	mModelAction.setAction((int)KeyBinding::Model_Random10, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.1); });
	mModelAction.setAction((int)KeyBinding::Model_Random15, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.15); });
	mModelAction.setAction((int)KeyBinding::Model_Random25, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.25); });
	mModelAction.setAction((int)KeyBinding::Model_Random50, [](Model & model, Controller & controller, View & view)-> void { model.randomiseMatrix(0.50); });
	
	//mModelAction.setAction((int)KeyBinding::Model_PrevRle, [](Model & model, Controller & controller, View & view)-> void { model.prevRle(); });
	//mModelAction.setAction((int)KeyBinding::Model_SameRle, [](Model & model, Controller & controller, View & view)-> void { model.sameRle(); });
	//mModelAction.setAction((int)KeyBinding::Model_NextRle, [](Model & model, Controller & controller, View & view)-> void { model.nextRle(); });

}