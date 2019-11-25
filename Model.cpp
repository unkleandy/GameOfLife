#include "Model.h"

// constructor
Model::Model( int dimX, int dimY) 
	: 
	mGoL{ dimX,dimY },
	rules{	{std::vector<int>{3},std::vector<int>{2,3}},
			{std::vector<int>{1,3},std::vector<int>{2,3}},
			{std::vector<int>{1,3,5,7},std::vector<int>{1,3,5,7}},
			{std::vector<int>{3,6},std::vector<int>{2,3}}
	}
{}

void Model::showRule() { mRule.afficherRule(); }
void Model::setCellMatrix(int x, int y) { mCM.setSize(x, y); }
void Model::update() { mGoL.evolveMatrix(); }

void Model::nextRule() 
{
	static std::vector<Rule>::iterator it{ rules.begin() };

	if (it == rules.end() - 1)
	{
		mRule = *it;
		it = rules.begin();
	}
	else 
	{
		mRule = *it;
		++it;
	}
}

void Model::randomiseMatrix(double precentage) {}

void Model::reinitialise() {}
CellMatrix & Model::cellmatrix() { return mCM; }
GameOfLife & Model::gol() { return mGoL; }
