// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	Rule Class
// Description	:	
// Authors		:	Andrea Cohen & Elisha Buhendwa
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _RULE_H_
#define _RULE_H_
#include <vector>	// for vector
#include "Cell.h"

class Rule
{
private:
	int mBorn;
	int mSurvive;

public:
	Rule();
	Rule(std::vector<int> born, std::vector<int> survive);
	// Modificateurs
	void setRule(std::vector<int> b, std::vector<int> s);
	int defineRule(std::vector<int> r);
	// Accesseurs
	int born();
	int survive();
	// Afficheur
	void afficher(int BornSurvive);
	void afficherBorn();
	void afficherSurvive();
	void afficherRule();
};

#endif // _RULE_H_