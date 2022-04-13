#include "Scanner.h"

ScannerClass::ScannerClass(std::string inputFileName) 
	: mFin(inputFileName.c_str(), std::ios::binary),
	mLineNumber(1) {
	// MSG("Initializing ScannerClass object");
	if (!mFin.is_open()) {
		std::cout << "Bad input file. " << std::endl;
	}
}

ScannerClass::~ScannerClass() {
	mFin.close();
}

TokenClass ScannerClass::PeekNextToken() {
	int lineNumber = mLineNumber;
	std::streamoff where = mFin.tellg();
	TokenClass result = GetNextToken();
	if (!mFin) {
		mFin.clear();
	}
	mFin.seekg(where);
	mLineNumber = lineNumber;
	return result;
}

TokenClass ScannerClass::GetNextToken() {
	StateMachineClass stateMachine;
	TokenType correspondingTokenType;
	MachineState currentState = START_STATE;
	std::string lexeme;
	
	do {
		char c = mFin.get();
		lexeme += c;
		if (c == '\r' || c == '\n') {
			mLineNumber++;
		}
		currentState = stateMachine.UpdateState(c, correspondingTokenType);
		if (currentState == START_STATE || currentState == ENDFILE_STATE) {
			lexeme = "";
		}
	} while (currentState != CANTMOVE_STATE);

	mFin.unget();
	lexeme.pop_back();
	
	TokenClass tt(correspondingTokenType, lexeme);
	tt.CheckReserved();
	
	if (correspondingTokenType == BAD_TOKEN) {
		std::cerr << "Bad token type on lexeme: " << lexeme << std::endl;
		exit(1);
	}
	
	// if (correspondingTokenType == NEWLINE_TOKEN) {
		// mLineNumber++;
	// }

	return tt;	 
}

int ScannerClass::GetLineNumber() {
	return mLineNumber;
}