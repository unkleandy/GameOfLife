


#include <regex>		// for std::regex, std::smatch, std::regex_search in setMatrixFromString() and readRLE()
#include <string>		// for std::string and stoi
#include <iostream>		// for testing
#include <cassert>		// for assert

// headers
#include "rleUtil.h"

int main()
{
	std::string txt="x = 76, y = 53, rule = B3/S23 \nobo$b2o$bo17$20bo$21b2o$20b2o5$51b2o$52bo$52bobo$42bo10b2o$40b3o$39bo$\n39b2o$24b2o48b2o$25bo48b2o$25bob2o$26bo2bo23bo$27b2o24bo$42b2o9b3o$42b\n2o11bo4$51bo3b2o$50bobo3bo$49bobo3bo$45b2obobo3bo$45b2obo2b4obo5b2o$\n49bobo3bobo5bo$45b2ob2o2bo2bobo2b3o$46bobo2b2o3bo3bo$34b2o10bobo$34b2o\n11bo!";
	RleUtil rle;
	rle.setDimRuleFromString(txt);

	return 0;
}
RleUtil::RleUtil() {} //:mCM{}{}

RleUtil::RleUtil(std::string path)
{
//TODO open fstream

	std::fstream fstream(path, std::ios::in);

	std::regex reComment("#[NnCcOcRr].*");
	std::regex reDimRule("[Xx] *= *\d\d* *, *[Yy] *= *\d\d* *, *[Rr]ule *= *[Bb]\d\d*\/[Ss]\d\d*");

	std::string line{};
	std::string dimRuleInfo{};
	std::string matrixInfo{};

	while (getline(fstream, line))

	{
		if (line.length() == 0) {}
		else if (std::regex_match(line, reComment)) {}
		else if (std::regex_match(line, reDimRule)) { dimRuleInfo = line; }
		else if (dimRuleInfo.length() != 0) { matrixInfo += line; }
	}

// testing
	std::cout << "RleUtil::RleUtil dimRuleInfo : "<< dimRuleInfo << std::endl;
	std::cout << "RleUtil::RleUtil matrixInfo : " << matrixInfo << std::endl;

	setDimRuleFromString(dimRuleInfo);
	setMatrixFromString(matrixInfo);

//TODO close fstream
}

//
//void RleUtil::nextLine(itCM& it, int mult)
//{
//	mult = mult ? mult : 1;
//	itCM start{ mCM.matrix().begin() };
//	it = start + (ceil(std::distance(start, it) / mCM.x()) + mult)*mCM.x();
//	assert(it < mCM.matrix().end());
//}


void RleUtil::setMatrixFromString(std::string str)
{

//TODO add regex to cut string at '!'	
	std::regex trim("(([[:space:]].*)*\!)");
	std::smatch trimStr;
	std::regex_search(str, trimStr, trim);
	str = trimStr.str(1);
	// the regex search ensures that there are no other characters 
	// and that the default switchcase will always be a number
	std::regex limitedChars("[ob\$[[:digit:]]]");
	std::smatch matches;
	std::regex_search(str, matches, limitedChars);
	itCM currentCell { mCM.matrix().begin() };
	int cellsInLine{};
	int cellLine{};

	std::string multiplier{ nullptr };
	char c{};
	for (int i{}; i<matches.size();++i)
	{
		c = matches.str(i)[0];
		switch(c)
		{
		case 'o':
			multiplier = std::stoi(multiplier) ? multiplier : "1";
			assert(currentCell + std::stoi(multiplier) < mCM.matrix().end());
			mCM.travelCellMatrix(Cell::setStateActive, currentCell, currentCell + std::stoi(multiplier));
			multiplier = "";
			break;
		case 'b':
			currentCell+=std::stoi(multiplier); 
			multiplier = ""; 
			break;
		case '$':
			nextLine(currentCell, std::stoi(multiplier));
			multiplier = "";
			
			break;
		default:
			multiplier += c;
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
	std::regex re("([XxYy]) *= *([[:digit:]]*) *, *([XxYy]) *= *([[:digit:]]*) *, *[Rr]ule *= *[Bb]?([[:digit:]]*)\/[Ss]?([[:digit:]]*)");
	std::string xDim{}, yDim{}, bRule{}, sRule{};
	std::smatch matches;

	std::regex_search(str, matches, re);
	toupper(matches.str(1)[0]) == 'X' ? xDim = (std::string) matches.str(2) : yDim = (std::string) matches.str(2);
	toupper(matches.str(2)[0]) == 'X' ? xDim = (std::string) matches.str(4) : yDim = (std::string) matches.str(4);
	
	sRule = (std::string) matches.str(5);
	bRule = (std::string) matches.str(6);
	

//testing
	std::cout << "RleUtil::setDimRuleFromString xDim : " << xDim << std::endl;
	std::cout << "RleUtil::setDimRuleFromString yDim : " << yDim << std::endl;
	std::cout << "RleUtil::setDimRuleFromString bRule : " << bRule << std::endl;
	std::cout << "RleUtil::setDimRuleFromString sRule : " << sRule << std::endl;
	//mRule.setRule(string2IntVect(bRule), string2IntVect(sRule));
	mCM.setSize(std::stoi(xDim), std::stoi(yDim));
}


// getters

//Rule RleUtil::rule()				{ return mRule; }

CellMatrix RleUtil::cellmatrix()	{ return mCM; }