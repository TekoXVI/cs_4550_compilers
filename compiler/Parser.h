#ifndef PARSER
#define PARSER

#include "Scanner.h"
#include "Token.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass {
public:
	ParserClass(ScannerClass *scanner, SymbolTableClass *symboltable);
	StartNode* Start();
	TokenClass Match(TokenType expectedType);
	ProgramNode* Program();
	BlockNode* Block();
	StatementGroupNode* StatementGroup();
	StatementNode* Statement();
	DeclarationStatementNode* DeclarationStatement();
	AssignmentStatementNode* AssignmentStatement();
	PlusEqualNode* PlusEqual();
	ExpressionNode* Expression();
	ExpressionNode* Relational();
	ExpressionNode* PlusMinus();
	ExpressionNode* TimesDivide();
	ExpressionNode* Exponent();
	ExpressionNode* Factor();
	IfNode* If();
	WhileNode* While();
	ExpressionNode* Or();
	ExpressionNode* And();
	IdentifierNode* Identifier();
	IntegerNode* Integer();
	CoutStatementNode* CoutStatement();
	
	CoutStatementNode* PrintStatement();
private:
	ScannerClass* mScanner;
	SymbolTableClass* mSymbolTable;
};

#endif