#include "Parser.h"
// #include "Node.h"
// #include "Symbol.h"
// #include "Token.h"
// #include "Scanner.h"
#include "Debug.h"
#include <iostream>


void test_scanner() {
	ScannerClass scanner("something.txt");
	TokenClass token;
	
	do {
		std::cout << "Line:   " << scanner.GetLineNumber() << std::endl;
		
		token = scanner.GetNextToken();
		std::cout << token << std::endl;

	} while (token.GetTokenType() != ENDFILE_TOKEN);
	
}

void test_symbol() {
	SymbolTableClass st = SymbolTableClass();
	st.AddEntry("hi");
	st.SetValue("hi", 20);
	st.GetValue("hi");
	st.AddEntry("world");
	st.SetValue("no", 100);
}

void test_parser() {
	ScannerClass scanner("something.txt");
	SymbolTableClass symbolTable = SymbolTableClass();
	ParserClass parser(&scanner, &symbolTable);
	StartNode* sn = parser.Start();
	
	delete sn;
}


void test_node() {

	SymbolTableClass symbolTable;
	
	// IntegerNode* in = new IntegerNode(3);
	IdentifierNode* in = new IdentifierNode("sum", &symbolTable);
	CoutStatementNode* csn = new CoutStatementNode(in);
	StatementGroupNode* sgn = new StatementGroupNode();
	sgn -> AddStatement(csn);
	BlockNode* bn = new BlockNode(sgn);
	ProgramNode* pn = new ProgramNode(bn);
	StartNode* sn = new StartNode(pn);
	
	delete sn;
	
	// sn -> Interpret();
	
	// sn -> Code();
	// sn -> Execute();
}

void test_interpret() {
	SymbolTableClass symbolTable;
	ScannerClass scanner("something.txt");
	ParserClass parser(&scanner, &symbolTable);
	StartNode* starter = parser.Start();
	starter->Interpret();
	delete starter;
}

int main() {
	// test_scanner();
	// test_symbol();
	// test_parser();
	// test_node();
	test_interpret();
	return 0;
}
