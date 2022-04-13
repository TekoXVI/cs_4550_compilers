#ifndef SCANNER
#define SCANNER

#include "StateMachine.h"
#include "Debug.h"

#include <fstream>
#include <iostream>

class ScannerClass {

public:
	ScannerClass(std::string inputFileName);
	~ScannerClass();
	TokenClass GetNextToken();
	int GetLineNumber();
	TokenClass PeekNextToken();
	
private:
	std::ifstream mFin;
	int mLineNumber;
};

#endif //SCANNER