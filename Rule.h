#pragma once

class Rule
{
private:
	int s;
	int b;
public:
	Rule() { s = 0; b = 0; }
	int survive();
	int born();


};


