#ifndef SCANNER
#define SCANNER

#include "Token.h"
#include "Debug.h"

#include <fstream>
#include <iostream>

class ScannerClass {

public:
	ScannerClass(std::string inputFileName);
	~ScannerClass();
	TokenClass GetNextToken();
	int GetLineNumber();
	
private:
	std::ifstream mFin;
	int mLineNumber;
};

#endif //SCANNER