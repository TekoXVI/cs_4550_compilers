#include "Token.h"
TokenClass::TokenClass() {
	
}

TokenClass::TokenClass(TokenType type, const std::string & lexeme) 
	: mType(type), mLexeme(lexeme) {}

void TokenClass::CheckReserved() {
	if (mLexeme == "void") {
		mType = VOID_TOKEN;
	} else if (mLexeme == "main") {
		mType = MAIN_TOKEN;
	} else if (mLexeme == "int") {
		mType = INT_TOKEN;
	} else if (mLexeme == "cout") {
		mType = COUT_TOKEN;
	} else if (mLexeme == "if") {
		mType = IF_TOKEN;
	} else if (mLexeme == "while") {
		mType = WHILE_TOKEN;
	} else if (mLexeme == "else") {
		mType = ELSE_TOKEN;
	} else if (mLexeme == "print") {
		mType = PRINT_TOKEN;
	} 
}

TokenType TokenClass::GetTokenType() const { 
	return mType; 
}

const std::string& TokenClass::GetTokenTypeName() const { 
	return gTokenTypeNames[mType]; 
}

std::string TokenClass::GetLexeme() const {
	return mLexeme; 
}

const std::string& TokenClass::GetTokenTypeName(TokenType type) { 
	return gTokenTypeNames[type]; 
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc) {
	out << "Lexeme: " << tc.GetLexeme() << std::endl;
	out << "Token:  " << tc.GetTokenTypeName() << std::endl;
	return out;
};
