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


class Controller
{
private:
	Model mModel;
	View mView;
	bool mQuit;

public:
	Controller(Model &, View &);
	~Controller();
	void run();
	void initaliseConsoleContext();
};

#endif // !_CONTROLLER_H_
