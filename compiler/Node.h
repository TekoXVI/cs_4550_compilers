#ifndef NODE
#define NODE

#include "Symbol.h"

#include <vector>
#include <string>

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class ExponentNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;
class IfNode;
class WhileNode;
class AndNode;
class OrNode;


class Node {
public:
	virtual ~Node() {
		
	}
	virtual void Interpret() = 0;
};


class StartNode: public Node {
public:
	StartNode(ProgramNode* pn);
	virtual ~StartNode();
	void Interpret();
	
private:
	ProgramNode* mProgramNode;
};


class ProgramNode: public Node {
public:
	ProgramNode(BlockNode* bn);
	virtual ~ProgramNode();
	void Interpret();

private:
	BlockNode* mBlockNode;
};

class StatementNode: public Node {
	
};


class BlockNode: public StatementNode {	
public:
	BlockNode(StatementGroupNode* sgn);
	virtual ~BlockNode();
	void Interpret();
	
private:
	StatementGroupNode* mStatementGroupNode;
};


class StatementGroupNode: public Node {
public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	void AddStatement(StatementNode* sn);
	void Interpret();
	
protected:
	std::vector<StatementNode*> mStatements;
};


class DeclarationStatementNode: public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode* in);
	virtual ~DeclarationStatementNode();
	void Interpret();
	
private:
	IdentifierNode* mIdentifierNode;
};


class AssignmentStatementNode: public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
	virtual ~AssignmentStatementNode();
	void Interpret();
	
private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};


class PlusEqualNode: public StatementNode {
public:
	PlusEqualNode(IdentifierNode* in, ExpressionNode* en);
	virtual ~PlusEqualNode();
	void Interpret();
	
private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};


class CoutStatementNode: public StatementNode {
public:	
	CoutStatementNode(ExpressionNode* en);
	virtual ~CoutStatementNode();
	void Interpret();
	
private:
	ExpressionNode* mExpressionNode;
};

class IfNode: public StatementNode {
public:
	IfNode(ExpressionNode* en, BlockNode* bn, BlockNode* bn2);
	virtual ~IfNode();
	void Interpret();
	
private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
	BlockNode* mBlockNode2;
};


class WhileNode: public StatementNode {
public:
	WhileNode(ExpressionNode* en, BlockNode* bn);
	virtual ~WhileNode();
	void Interpret();
	
private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
};


class ExpressionNode {
public:
	virtual ~ExpressionNode() {
		
	}
	virtual int Evaluate() = 0;
};

class IntegerNode: public ExpressionNode {
public:
	IntegerNode(int i);
	int Evaluate();
private:
	int mI;
};


class IdentifierNode: public ExpressionNode {
public:	
	IdentifierNode(std::string label, SymbolTableClass* symboltable);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	int Evaluate();
private:
	std::string mLabel;
	SymbolTableClass* mSymbolTable;
};


class BinaryOperatorNode: public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
	virtual ~BinaryOperatorNode();
protected:
	ExpressionNode* mLeft;
	ExpressionNode* mRight;
};

class AndNode: public BinaryOperatorNode {
public:
	AndNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class OrNode: public BinaryOperatorNode {
public:
	OrNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class PlusNode: public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};


class MinusNode: public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class TimesNode: public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class DivideNode: public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class ExponentNode: public BinaryOperatorNode {
public:
	ExponentNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class LessNode: public BinaryOperatorNode {
public:
	LessNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class LessEqualNode: public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class GreaterNode: public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class GreaterEqualNode: public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class EqualNode: public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};

class NotEqualNode: public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
};



#endif