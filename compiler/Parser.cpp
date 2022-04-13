#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symboltable) 
	: mScanner(scanner), mSymbolTable(symboltable) {
	
}

StartNode* ParserClass::Start() {
	ProgramNode *pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode *sn = new StartNode(pn);
	return sn;
}

TokenClass ParserClass::Match(TokenType expectedType) {
	TokenClass currentToken = mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType) {
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Scanning line " << mScanner->GetLineNumber() << std::endl;
		std::cerr << "Expected token type " << 
			TokenClass:: GetTokenTypeName(expectedType) << 
			", but got type " << currentToken.GetTokenTypeName() << std::endl;
		exit(1);
	}
	// std::cout << "\tSuccessfully matched Token Type: " <<
		// currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		// currentToken.GetLexeme() << "\"" << std::endl;
	return currentToken; // the one we just processed
}

ProgramNode* ParserClass::Program() {
	// std::cout << "Starting Program. " << std::endl;
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *bn = Block();
	ProgramNode *pn = new ProgramNode(bn);
	// std::cout << "Program finished. " << std::endl;
	return pn;
}

BlockNode* ParserClass::Block() {
	// std::cout << "Starting Block. " << std::endl;
	Match(LCURLY_TOKEN);
	StatementGroupNode *sgn = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode *bn = new BlockNode(sgn);
	// std::cout << "Block finished. " << std::endl;
	return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
	// std::cout << "Starting Statement Group. " << std::endl;
	StatementGroupNode *sgn = new StatementGroupNode();
	while (true) {
		StatementNode *sn = Statement();
		if (sn != NULL) {
			sgn->AddStatement(sn);
		} else {
			break;
		}
	} return sgn;
}

StatementNode* ParserClass::Statement() {
	// std::cout << "Starting Statement. " << std::endl;
	StatementNode *sn = NULL;
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == INT_TOKEN) {
		sn = DeclarationStatement();
	} else if (tt == IDENTIFIER_TOKEN) {
		sn = AssignmentStatement();
	} else if (tt == COUT_TOKEN) {
		// std::cout << "found cout statement" << std::endl;
		sn = CoutStatement();
	} else if (tt == IF_TOKEN) {
		sn = If();
	} else if (tt == WHILE_TOKEN) {
		sn = While();
	} else if (tt == PRINT_TOKEN) {
		sn = PrintStatement();
	}
	
	return sn;
}

DeclarationStatementNode* ParserClass::DeclarationStatement() {
	// std::cout << "Starting Declaration Statement. " << std::endl;
	Match(INT_TOKEN);
	IdentifierNode *in = Identifier();
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode *dn = new DeclarationStatementNode(in);
	return dn;
}

AssignmentStatementNode* ParserClass::AssignmentStatement() {
	// std::cout << "Starting Assignment Statement. " << std::endl;
	IdentifierNode* in = Identifier();
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	AssignmentStatementNode *an = new AssignmentStatementNode(in, en);
	return an;
}

PlusEqualNode* ParserClass::PlusEqual() {
	IdentifierNode* in = Identifier();
	Match(PLUSEQUAL_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	PlusEqualNode* p = new PlusEqualNode(in, en);
	return p;
}

ExpressionNode* ParserClass::Expression() {
	// std::cout << "Starting Expression. " << std::endl;
	ExpressionNode *current = Or();
	return current;
}

ExpressionNode* ParserClass::Or() {
	ExpressionNode* current = And();
	while (true) {
		TokenType tt = mScanner -> PeekNextToken().GetTokenType();
		if (tt == OR_TOKEN) {
			Match(tt);
			current = new OrNode(current, And());
		} else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::And() {
	ExpressionNode* current = Relational();
	while (true) {
		TokenType tt = mScanner -> PeekNextToken().GetTokenType();
		if (tt == AND_TOKEN) {
			Match(tt);
			current = new AndNode(current, Relational());
		} else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::Relational() {
	ExpressionNode* current = PlusMinus();
	// Handle the optional tail:
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN) {
		Match(tt);
		current = new LessNode(current, PlusMinus());
	} else if (tt == LESSEQUAL_TOKEN) {
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	} else if (tt == GREATER_TOKEN) {
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	} else if (tt == GREATEREQUAL_TOKEN) {
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	} else if (tt == EQUAL_TOKEN) {
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	} else if (tt == NOTEQUAL_TOKEN) {
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	} else {
		return current;
	}
	return current;
}

ExpressionNode* ParserClass::PlusMinus() {
	ExpressionNode *current = TimesDivide();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN) {
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		} else if (tt == MINUS_TOKEN) {
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		} else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::TimesDivide() {
	ExpressionNode* current = Exponent();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current, Exponent());
		} else if(tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current, Exponent());
		} else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::Exponent() {
	ExpressionNode* current = Factor();
	while (true) {
		TokenType tt = mScanner -> PeekNextToken().GetTokenType();
		if (tt == EXPONENT_TOKEN) {
			Match(tt);
			current = new ExponentNode(current, Factor());
		} else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::Factor() {
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		IdentifierNode *id = Identifier();
		return id;
	} else if (tt == INTEGER_TOKEN) {
		IntegerNode *in = Integer();
		return in;
	} else if (tt == LPAREN_TOKEN) {
		Match(LPAREN_TOKEN);
		ExpressionNode *en = Expression();
		Match(RPAREN_TOKEN);
		return en;
	} else {
		std::cout << "Not a factor. " << std::endl;
		exit(1);
	}
}

IdentifierNode* ParserClass::Identifier() {
	TokenClass t = Match(IDENTIFIER_TOKEN);
	IdentifierNode *in = new IdentifierNode(t.GetLexeme(), mSymbolTable);
	return in;
}

IntegerNode* ParserClass::Integer() {
	TokenClass t = Match(INTEGER_TOKEN);
	IntegerNode *in = new IntegerNode(atoi(t.GetLexeme().c_str()));
	return in;
}

CoutStatementNode* ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode* E = Expression();
	Match(SEMICOLON_TOKEN);
	CoutStatementNode* cn = new CoutStatementNode(E);
	return cn;
}

CoutStatementNode* ParserClass::PrintStatement() {
	Match(PRINT_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* e = Expression();
	Match(RPAREN_TOKEN);
	Match(SEMICOLON_TOKEN);
	CoutStatementNode* cn = new CoutStatementNode(e);
	return cn;
}

IfNode* ParserClass::If() {
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* e = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* b = Block();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == ELSE_TOKEN) {
		Match(ELSE_TOKEN);
		BlockNode* b2 = Block();
		IfNode* i = new IfNode(e, b, b2);
		return i;
	} else {
		IfNode* i = new IfNode(e, b, NULL);
		return i;
	}
}

WhileNode* ParserClass::While() {
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* e = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* b = Block();
	WhileNode* a = new WhileNode(e, b);
	return a;
}
