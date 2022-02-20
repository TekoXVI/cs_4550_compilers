#include "StateMachine.h"
#include "Scanner.h"
#include "Debug.h"
#include <iostream>

int main() {
	ScannerClass scanner("something.txt");
	TokenClass token;
	
	do {
		std::cout << "Line:   " << scanner.GetLineNumber() << std::endl;
		
		token = scanner.GetNextToken();
		std::cout << token << std::endl;

	} while (token.GetTokenType() != ENDFILE_TOKEN);
	
	return 0;
}
