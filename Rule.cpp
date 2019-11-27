#include "Rule.h"
#include <string>
#include <vector>
#include <iostream>

// empty constructor
Rule::Rule()	: mBorn{ defineRule({3}) }, mSurvive{ defineRule({2,3}) } {}

Rule::Rule(std::vector<int> born, std::vector<int> survive) { setRule(born, survive); }


void Rule::setRule(std::vector<int> b, std::vector<int> s)
{
	mBorn = defineRule(b);
	mSurvive = defineRule(s);
}

int Rule::defineRule(std::vector<int> r)
{
	int rule{};
	for (int i{}; i < r.size(); ++i) 
	{
		rule = rule | 1 << r.at(i);
	}
	return rule;
}

void Rule::setRuleTo(Rule rule)
{
	mBorn = rule.mBorn;
	mSurvive = rule.mSurvive;
}


int Rule::born()
{
	return mBorn;
}

int Rule::survive()
{
	return mSurvive;
}

void Rule::afficher(int BornSurvive)
{
	std::string regle{};
	for (int i{}; i < 10; ++i) {
		if (BornSurvive >> i & 1)
			regle += i + '0';
	}
	std::cout << regle;
}

void Rule::afficherBorn()
{
	std::string regle{};
	for (int i{}; i < 10; ++i) {
		if(mBorn >> i & 1)
			regle+=i+'0';
	}
	std::cout << regle;
}

void Rule::afficherSurvive()
{
	std::string regle{};
	for (int i{}; i < 10; ++i) {
		if (mSurvive>> i & 1)
			regle += i + '0';
	}
	std::cout << regle;
}

void Rule::afficherRule()
{
	std::cout << "B";
	afficher(mBorn);
	std::cout << " S";
	afficher(mSurvive);
	std::cout << std::endl;
}













