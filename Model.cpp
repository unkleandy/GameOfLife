#include "Model.h"
#include <filesystem>

// constructor
Model::Model( int dimX, int dimY) 
	: 
	mGoL{ dimX,dimY },
	mRules{	{std::vector<int>{3},std::vector<int>{2,3}},
			{std::vector<int>{1,3},std::vector<int>{2,3}},
			{std::vector<int>{1,3,5,7},std::vector<int>{1,3,5,7}},
			{std::vector<int>{3,6},std::vector<int>{2,3}}
	}, 
	mRle{}
{
	using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
	for (const auto& dirEntry : recursive_directory_iterator("./fichiers_test_rle/"))
		mRLEs.push_back(dirEntry.path().string());
	mRLEsIt = mRLEs.begin();
	if (mRle.openFile(*mRLEsIt) == 0)
	{
		mGoL.importAndCenterCellmatrix(mRle.cellmatrix());
		if (mRle.rule().born() != 0 && mRle.rule().survive() != 0)
		{
			mRule = mRle.rule();
		}
	}
	else nextRle();
	
}

void Model::showRule() { mRule.afficherRule(); }
void Model::update() { mGoL.evolveMatrix(); }

void Model::nextRule() 
{
	mRulesIt = mRulesIt == mRules.end() - 1 ? mRulesIt = mRules.begin() : mRulesIt + 1;
	mGoL.rule().setRuleTo(*mRulesIt);
}

void Model::randomiseMatrix(double percentage) { mGoL.cellmatrix().randomizeMatrix(percentage); }

void Model::reinitialise() {}
CellMatrix & Model::cellmatrix() { return mGoL.cellmatrix(); }
GameOfLife & Model::gol() { return mGoL; }

void Model::importRle()
{
	mGoL.importAndCenterCellmatrix(mRle.cellmatrix());
	mGoL.rule() = mRle.rule();
	mRulesIt = mRules.begin();
}

void Model::prevRle()
{
	mRLEsIt = mRLEsIt == mRLEs.begin() ? mRLEs.end() - 1 : mRLEsIt - 1;
	if (mRle.openFile(*mRLEsIt) != 0)
	{
		prevRle();
	}
	else
	{
		importRle();
	}
}

void Model::nextRle()
{
	mRLEsIt = mRLEsIt == mRLEs.end() - 1 ? mRLEs.begin() : mRLEsIt + 1;
	if (mRle.openFile(*mRLEsIt) != 0)
	{
		nextRle();
	}
	else
	{
		importRle();
	}
}

void Model::sameRle() { mGoL.importAndCenterCellmatrix(mRle.cellmatrix()); }


