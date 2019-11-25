// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	Controler Class and MAIN in Controller.cpp
// Description	:	
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Model.h"
#include "View.h"
#include "EcaActionKeyBinding.h"


class Controller
{
private:
	Model mModel;
	View mView;
	bool mQuit{ false };
	int mSpeed{ 500 };
	ConsoleKeyReader & mReader;
	

public:
	Controller(Model & model, View & view);
	~Controller();
	void run();
	void initaliseConsoleContext();
	void keybinding();
	void quit();
	void changeSpeed(unsigned int);



private: 
	// adaptation du code de JC

	EcaActionKeyBinding mModelAction;

	enum class KeyBinding : char {
		Action_Quit = 27,	// escape character

		Controler_Speed1 = '1',
		Controler_Speed2 = '2',
		Controler_Speed3 = '3',
		Controler_Speed4 = '4',
		Controler_Speed5 = '5',
		Controler_Speed6 = '6',
		Controler_Speed7 = '7',
		Controler_Speed8 = '8',
		Controler_Speed9 = '9',

		Model_NextRule = 'R',
		Model_ToggleBorder = 'B',

		Console_SwitchColor = 'P',
		Console_toggleBg = 'O',

		Model_Random01 = 'A',
		Model_Random05 = 'S',
		Model_Random10 = 'D',
		Model_Random15 = 'F',
		Model_Random25 = 'G',
		Model_Random50 = 'H',

		Model_PrevRle = 'Z',
		Model_SameRle = 'X',
		Model_NextRle = 'W',
		_count_
	};
};

#endif // !_CONTROLLER_H_
