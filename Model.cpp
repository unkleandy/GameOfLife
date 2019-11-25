#include "Model.h"

// constructor
Model::Model( int dimX, int dimY) 
	: 
	mGoL{ dimX,dimY },
	mRules{	{std::vector<int>{3},std::vector<int>{2,3}},
			{std::vector<int>{1,3},std::vector<int>{2,3}},
			{std::vector<int>{1,3,5,7},std::vector<int>{1,3,5,7}},
			{std::vector<int>{3,6},std::vector<int>{2,3}}
	},
	mRles{}
{}

void Model::showRule() { mRule.afficherRule(); }
void Model::update() { mGoL.evolveMatrix(); }

void Model::nextRule() 
{
	static std::vector<Rule>::iterator it{ mRules.begin() };

	if (it == mRules.end() - 1)
	{
		mRule = *it;
		it = mRules.begin();
	}
	else 
	{
		mRule = *it;
		++it;
	}
}

void Model::randomiseMatrix(double precentage) {}

void Model::reinitialise() {}
CellMatrix & Model::cellmatrix() { return mGoL.cellmatrix(); }
GameOfLife & Model::gol() { return mGoL; }
