#include "Model.h"



// constructor
Model::Model() : mGoL{ 0, 0 } { mCM.setSize(0, 0); mRule.setRule({}, {}); }


void Model::setCellMatrix(int x, int y) { mCM.setSize(x, y); }
void Model::update() {}
void Model::nextrule() {}
void Model::reinitialise() {}
CellMatrix & Model::cellmatrix() { return mCM; }
GameOfLife & Model::gol() { return mGoL; }

