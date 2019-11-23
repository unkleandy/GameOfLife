


#include <regex>		// for std::regex, std::smatch, std::regex_search in setMatrixFromString() and readRLE()
#include <string>		// for std::string and stoi
#include <iostream>		// for testing
#include <cassert>		// for assert
#include <filesystem>

// headers
#include "rleUtil.h"

//int main()
//{
//	std::string txt="x = 76, y = 53, rule = B3/S23 ";
//	std::string matrix = "\nobo$b2o$bo17$20bo$21b2o$20b2o5$51b2o$52bo$52bobo$42bo10b2o$40b3o$39bo$\n39b2o$24b2o48b2o$25bo48b2o$25bob2o$26bo2bo23bo$27b2o24bo$42b2o9b3o$42b\n2o11bo4$51bo3b2o$50bobo3bo$49bobo3bo$45b2obobo3bo$45b2obo2b4obo5b2o$\n49bobo3bobo5bo$45b2ob2o2bo2bobo2b3o$46bobo2b2o3bo3bo$34b2o10bobo$34b2o\n11bo!";
//	RleUtil rle;
//	rle.setDimRuleFromString(txt);
//	rle.setMatrixFromString(matrix);
//	rle.cellmatrix().show();
//	return 0;
//}


RleUtil::RleUtil() :mCM{} {}

RleUtil::RleUtil(std::string path)
{
//TODO open fstream

	std::ifstream file(path);
	if (file.is_open())
	{
		std::regex reComment("#[NnCcOcRr].*");
		std::regex reDimRule("[Xx] *= *[[:digit:]][[:digit:]]*, *[Yy].*");
		std::regex reLastLine("[ob\\$\\d]*!.*");

		std::string line{};
		std::string dimRuleInfo{};
		std::string matrixInfo{};
		bool info{};
		bool lastline{};

		while (getline(file, line))
		{
			if (line.length() == 0) {}
			else if (std::regex_match(line, reComment)) { std::cout << "RleUtil::RleUtil commentaire  : " + line << std::endl; }
			else if (std::regex_match(line, reDimRule)) { dimRuleInfo = line; bool info = true;   std::cout << "RleUtil::RleUtil dim et regle  : " + dimRuleInfo << std::endl; }
			else if (std::regex_match(line, reLastLine)) { lastline = true;  matrixInfo += line; std::cout<<"RleUtil::RleUtil last line  : " + matrixInfo << std::endl;}
			else if (info == true && lastline == false) { matrixInfo += line; std::cout << "RleUtil::RleUtil matrice  : " + matrixInfo << std::endl; }
		}

		// testing
		std::cout << "RleUtil::RleUtil dimRuleInfo : " << dimRuleInfo << std::endl;
		std::cout << "RleUtil::RleUtil matrixInfo : " << matrixInfo << std::endl;

		setDimRuleFromString(dimRuleInfo);
		setMatrixFromString(matrixInfo);

		//TODO close fstream
	}
}


void RleUtil::nextLine(itCM& it, int mult)
{
	mult = mult ? mult : 1;
	itCM start{ mCM.matrix().begin() };
	it = start + (ceil(std::distance(start, it) / mCM.x()) + mult)*mCM.x();
	assert(it < mCM.matrix().end());
}


void RleUtil::setMatrixFromString(std::string str)
{

	itCM currentCell { mCM.matrix().begin() };
	int cellsInLine{};
	int cellLine{};

	std::string multiplier{};
	int mult{};

	for (int i{}; i<str.length();++i)
	{	
		switch(str[i])
		{
		case 'o':
			mult = ((multiplier.size()==0) ? 1 : stoi(multiplier));
			assert(currentCell + std::stoi(multiplier) < mCM.matrix().end());
			mCM.travelCellMatrix(&Cell::setStateActive, currentCell, currentCell + mult);
			multiplier = "";
			break;
		case 'b':
			mult = ((multiplier.size() == 0) ? 1 : stoi(multiplier));
			currentCell+=mult;
			multiplier = ""; 
			break;
		case '$':
			mult = ((multiplier.size() == 0) ? 1 : stoi(multiplier));
			nextLine(currentCell, mult);
			multiplier = "";
			break;
		case '\n': 
		case '\r':
			break;
		default:
			multiplier += str[i];
			break;
		}

		if (cellsInLine >= mCM.x()) { std::cout << "CellMatrix width exeeded" << std::endl; }
		//TODO open next RLEfile
		if (cellLine >= mCM.y()) { std::cout << "CellMatrix height exeeded" << std::endl; }
		//TODO open next RLEfile
	}
}


std::vector<int> RleUtil::string2IntVect(std::string str)
{
	std::vector<int> vec{};
	for (char c : str)
	{
		// (c-'0') turns the c char representation of an int to its int value, equiv to (c-48)
		vec.push_back(c-'0');
	}
	return vec;
}


void RleUtil::setDimRuleFromString(std::string str)
{
	std::regex re("([XxYy]) *= *([[:digit:]]*) *, *([XxYy]) *= *([[:digit:]]*) *, *[Rr]ule *= *[Bb]?([[:digit:]]*)\\/[Ss]?([[:digit:]]*)");
	std::string xDim{}, yDim{}, bRule{}, sRule{};
	std::smatch matches;

	std::regex_search(str, matches, re);
	toupper(matches.str(1)[0]) == 'X' ? xDim = (std::string) matches.str(2) : yDim = (std::string) matches.str(2);
	toupper(matches.str(2)[0]) == 'X' ? xDim = (std::string) matches.str(4) : yDim = (std::string) matches.str(4);
	
	sRule = (std::string) matches.str(5);
	bRule = (std::string) matches.str(6);
	

////testing
//	std::cout << "RleUtil::setDimRuleFromString xDim : " << xDim << std::endl;
//	std::cout << "RleUtil::setDimRuleFromString yDim : " << yDim << std::endl;
//	std::cout << "RleUtil::setDimRuleFromString bRule : " << bRule << std::endl;
//	std::cout << "RleUtil::setDimRuleFromString sRule : " << sRule << std::endl;

	mRule.setRule(string2IntVect(bRule), string2IntVect(sRule));
	mCM.setSize(std::stoi(xDim), std::stoi(yDim));
}


// getters

Rule RleUtil::rule()				{ return mRule; }

CellMatrix & RleUtil::cellmatrix()	{ return mCM; }