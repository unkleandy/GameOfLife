// Context		:	A2019 420-B52 Travail-Pratique 1
// Teacher		:	Jean-Christophe Demers
// Contents		:	RleUtil Class
// Description	:	Enables the translation of an RLE file to a Matrix and Rule
// Autrice		:	Andrea Cohen
// Date			:	2019-11-16
// Comments		:	


#pragma once
#ifndef _RLEUTIL_H_5
#define _RLEUTIL_H_


#include "CellMatrix.h"
#include "Rule.h"
#include <fstream>
#include <string>
#include <vector>


class RleUtil
{
private:
	Rule mRule;
	CellMatrix mCM;
	std::vector<int> string2IntVect(std::string str);
	void nextLine(itCM& it, int mult);
public:
	void setMatrixFromString( std::string );
	//void setMatrixFromSmatch(const std::smatch &);
	void setDimRuleFromString(std::string str);
	RleUtil(std::string path);
	RleUtil();
	// getters
	Rule rule();
	CellMatrix & cellmatrix();
};


#endif // !_RLEUTIL_H_
