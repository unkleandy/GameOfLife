


#include <regex>		// for std::regex, std::smatch, std::regex_search in setMatrixFromString() and readRLE()
#include <string>		// for std::string and stoi
#include <iostream>		// for testing
#include <cassert>		// for assert
#include <filesystem>

// headers
#include "rleUtil.h"
#include "Main.h"


RleUtil::RleUtil()
	:
	mCM{},
	mRule { {2, 3}, { 2 }}
{
	
}


int RleUtil::openFile(std::string path)
{
//TODO open fstream
	std::cout << path << std::endl;
	std::ifstream file(path);
	if (file.is_open())
	{
		std::regex reComment("#[NnCcOcRr].*");
		std::regex reDimRule("[Xx] *= *\\d\\d*, *[Yy].*");
		std::regex reMatrixLine("[ob\\$\\d][ob\\$\\d]*.*");
		std::regex reLastLine("[ob\\$\\d]*!.*");

		std::string line{};
		std::string dimRuleInfo{};
		std::string matrixInfo{};
		bool info{};
		bool lastline{};

		while (getline(file, line))
		{
			if (line.length() == 0) {}
			else if (std::regex_match(line, reComment)) { std::cout << "RleUtil::openFile commentaire  : " + line << std::endl; }
			else if (std::regex_match(line, reDimRule)) 
			{ 
				info = true;
				dimRuleInfo = line; 
				std::cout << "RleUtil::openFile dim et regle  : " + dimRuleInfo << std::endl; 
			}
			else if (std::regex_match(line, reLastLine)) 
			{ 
				lastline = true;  
				matrixInfo += line; 
				std::cout << "RleUtil::openFile matrixInfo : " + matrixInfo<< std::endl;
				break; 
			}
			else if (std::regex_match(line, reMatrixLine)) { matrixInfo += line; }
			else if (lastline == false) { return-1; }
		}

		// testing
		//std::cout << "RleUtil::RleUtil dimRuleInfo : " << dimRuleInfo << std::endl;
		//std::cout << "RleUtil::RleUtil matrixInfo : " << matrixInfo << std::endl;
		if (info == false)
		{
			std::cout << "RleUtil::openFile no rule info" << std::endl;
			return -1;
		}
		else if (!lastline)
		{
			std::cout << "RleUtil::openFile no last line" << std::endl;
			return -1;
		}
		else if (setDimRuleFromString(dimRuleInfo) != 0)
		{
			std::cout << "RleUtil::openFile failed setDimRuleFromString" << std::endl;
			return -1;
		}
		else if (setMatrixFromString(matrixInfo) != 0)
		{
			std::cout << "RleUtil::openFile failed setMatrixFromString" << std::endl;
			return -1;
		}
		else
		{
			file.close();
			return 0;
		}
	}
	else return -1;
}


void RleUtil::nextLine(itCM& it, int mult)
{
	itCM start{ mCM.matrix().begin() };
	it = start + (ceil(std::distance(start, it) / mCM.x()) + mult)*mCM.x();
}


int RleUtil::setMatrixFromString(std::string str)
{
	itCM start = mCM.matrix().begin();
	itCM end = mCM.matrix().end();
	itCM currentCell { start };
	int cellsInLine{};
	int cellLine{};

	std::string multiplier{};
	int mult{};
	bool deadCellsOnly{ true };

	for (int i{}; i<str.length();++i)
	{	
		switch(str[i])
		{
		case 'o':
			mult = ((multiplier.size()==0) ? 1 : stoi(multiplier));
			if (std::distance(start, end) < std::distance(start, currentCell) + mult) { return-1; }
			mCM.travelCellMatrix(&Cell::setStateActive, currentCell, currentCell + mult);
			deadCellsOnly = false;
			multiplier = "";
			break;
		case 'b':
			mult = ((multiplier.size() == 0) ? 1 : stoi(multiplier));
			if (std::distance(start, end) < std::distance(start, currentCell) + mult){ return-1; }
			currentCell+=mult;
			multiplier = ""; 
			break;
		case '$':
			mult = ((multiplier.size() == 0) ? 1 : stoi(multiplier));
			if (std::distance(start, end) >= (floor(std::distance(start, currentCell) / mCM.x()) + mult)*mCM.x())
			{
				nextLine(currentCell, mult);	
			}
			else { return -1; }
			cellLine += mult;
			multiplier = "";
			break;
		case '\n': 
		case '\r':
		case ' ':
			break;
		default:
			multiplier += str[i];
			break;
		}

	}
	if (deadCellsOnly) 
	{ 
		std::cout << "RleUtil::setMatrixFromString deadCells only" << std::endl;
		return -1; 
	}
	else if (cellLine > mCM.y()) 
	{ 
		std::cout << "CellMatrix height exeeded" << std::endl; 
		return -1; 
	}
	else
	{
		std::cout << "no problen should run" << std::endl; 
		return 0;
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


int RleUtil::setDimRuleFromString(std::string str)
{
	std::regex reDim("([XxYy]) *= *(\\d\\d*) *, *([XxYy]) *= *(\\d\\d*)");
	std::regex reRule("[Rr]ule? *= *[Bb]?(\\d*)\\/[Ss]?(\\d*)");
	std::string xDim{}, yDim{}, bRule{}, sRule{};
	std::smatch matchesDim;
	std::smatch matchesRule;

	std::regex_search(str, matchesDim, reDim);
	if (!matchesDim.empty())
	{
		toupper(matchesDim.str(1)[0]) == 'X' ? xDim = (std::string) matchesDim.str(2) : yDim = (std::string) matchesDim.str(2);
		toupper(matchesDim.str(2)[0]) == 'X' ? xDim = (std::string) matchesDim.str(4) : yDim = (std::string) matchesDim.str(4);
		int x = stoi(xDim);
		int y = stoi(yDim);
		if (x>dim || y>dim ||x<2||y<2)
		{
			std::cout << "dim inapropriate"<<std::endl;
			return -1;
		}
		else
		{
			mCM.setSize(x, y);
			return 0;
		}
	}
	else return -1;

	std::regex_search(str, matchesRule, reRule);
	if (!matchesRule.empty())
	{
		sRule = (std::string) matchesRule.str(1);
		bRule = (std::string) matchesRule.str(2);
		mRule.setRule(string2IntVect(bRule), string2IntVect(sRule));
	}	
}


// getters

Rule RleUtil::rule()				{ return mRule; }

CellMatrix & RleUtil::cellmatrix()	{ return mCM; }