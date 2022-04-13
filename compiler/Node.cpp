#include "Node.h"

StartNode::StartNode(ProgramNode* pn) 
	: mProgramNode(pn) {
	mProgramNode = new ProgramNode(*pn);
}

StartNode::~StartNode() {
	delete mProgramNode;
}

void StartNode::Interpret() {
	// std::cout << "SI" << std::endl;
	mProgramNode -> Interpret();
}

ProgramNode::ProgramNode(BlockNode* bn)
	: mBlockNode(bn) {
}

ProgramNode::~ProgramNode() {
	delete mBlockNode;
}

void ProgramNode::Interpret() {
	// std::cout << "PI" << std::endl;
	mBlockNode -> Interpret();
}

BlockNode::BlockNode(StatementGroupNode* sgn)
	: mStatementGroupNode(sgn) {
	}
	
BlockNode::~BlockNode() {
	delete mStatementGroupNode;
}

void BlockNode::Interpret() {
	// std::cout << "BI" << std::endl;
	mStatementGroupNode -> Interpret();
}

StatementGroupNode::StatementGroupNode() {
	
}

StatementGroupNode::~StatementGroupNode() {
	for (unsigned int i = 0; i < mStatements.size(); i++) {
		delete mStatements[i];
	}
}

void StatementGroupNode::AddStatement(StatementNode* sn) {
	// std::cout << "adding a statement" << std::endl;
	// std::cout << mStatements.size() << std::endl;
	mStatements.push_back(sn);
	// std::cout << mStatements.size() << std::endl;
}

void StatementGroupNode::Interpret() {
	// std::cout << "SGNI" << std::endl;
	// std::cout << mStatements.size() << std::endl;
	for (unsigned int i = 0; i < mStatements.size(); i++) {
		// std::cout << "SNI" << std::endl;
		mStatements[i] -> Interpret();
	}
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in) 
	: mIdentifierNode(in) {
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
}

void DeclarationStatementNode::Interpret() {
	mIdentifierNode -> DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en) 
	: mIdentifierNode(in), mExpressionNode(en) {
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
}

void AssignmentStatementNode::Interpret() {
	int value = mExpressionNode -> Evaluate();
	mIdentifierNode -> SetValue(value);
}

PlusEqualNode::PlusEqualNode(IdentifierNode* in, ExpressionNode* en)
	: mIdentifierNode(in), mExpressionNode(en) {
}

PlusEqualNode::~PlusEqualNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
}

void PlusEqualNode::Interpret() {
	int value = mExpressionNode -> Evaluate();
	value = value + mIdentifierNode->Evaluate();
	mIdentifierNode -> SetValue(value);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* en) 
	: mExpressionNode(en) {
	
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
}

void CoutStatementNode::Interpret() {
	// std::cout << "CI" << std::endl;
	int value = mExpressionNode -> Evaluate();
	std::cout << value << std::endl;
}



IfNode::IfNode(ExpressionNode* en, BlockNode* bn, BlockNode* bn2) 
	: mExpressionNode(en), mBlockNode(bn), mBlockNode2(bn2) {
}

IfNode::~IfNode() {
	delete mExpressionNode;
}

void IfNode::Interpret() {
	if (mExpressionNode -> Evaluate()) {
		mBlockNode -> Interpret();
	} else {
		if (mBlockNode2 != NULL) {
			mBlockNode2 -> Interpret();
		}
	} 
}

WhileNode::WhileNode(ExpressionNode* en, BlockNode* bn) 
	: mExpressionNode(en), mBlockNode(bn) {
}

WhileNode::~WhileNode() {
	delete mExpressionNode;
}

void WhileNode::Interpret() {
	while (mExpressionNode -> Evaluate()) {
		mBlockNode -> Interpret(); 
	}
}

IntegerNode::IntegerNode(int i) 
	: mI(i) {
		
}

int IntegerNode::Evaluate() {
	return mI;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* symboltable) 
	: mLabel(label), mSymbolTable(symboltable) {
	
}

void IdentifierNode::DeclareVariable() {
	mSymbolTable -> AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
	mSymbolTable -> SetValue(mLabel, v);
}

int IdentifierNode::GetIndex() {
	return mSymbolTable -> GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
	return mSymbolTable -> GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right) 
	: mLeft(left), mRight(right) {
	
}
	
BinaryOperatorNode::~BinaryOperatorNode() {
	delete mLeft;
	delete mRight;
}

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int PlusNode::Evaluate() {
	return mLeft -> Evaluate() + mRight -> Evaluate();
} 

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int MinusNode::Evaluate() {
	return mLeft -> Evaluate() - mRight -> Evaluate();
} 

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int TimesNode::Evaluate() {
	return mLeft -> Evaluate() * mRight -> Evaluate();
} 

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int DivideNode::Evaluate() {
	return mLeft -> Evaluate() / mRight -> Evaluate();
} 

ExponentNode::ExponentNode(ExpressionNode* left, ExpressionNode* right) 
	: BinaryOperatorNode(left, right) {
}

int ExponentNode::Evaluate() {
	int answer = mLeft->Evaluate(); 
	for (int i = 0; i < mRight->Evaluate() - 1; i++) {
		answer *= mLeft->Evaluate();
	}
	return answer;
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int LessNode::Evaluate() {
	if (mLeft < mRight) {
		return 1;
	} else {
		return 0;
	}
} 
LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int LessEqualNode::Evaluate() {
	if (mLeft <= mRight) {
		return 1;
	} else {
		return 0;
	}
} 
GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int GreaterNode::Evaluate() {
	if (mLeft > mRight) {
		return 1;
	} else {
		return 0;
	}
} 
GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int GreaterEqualNode::Evaluate() {
	if (mLeft >= mRight) {
		return 1;
	} else {
		return 0;
	}
} 
EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int EqualNode::Evaluate() {
	if (mLeft == mRight) {
		return 1;
	} else {
		return 0;
	}
} 
NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int NotEqualNode::Evaluate() {
	if (mLeft != mRight) {
		return 1;
	} else {
		return 0;
	}
} 

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int AndNode::Evaluate() {
	return mLeft -> Evaluate() && mRight -> Evaluate();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}


int OrNode::Evaluate() {
	return mLeft -> Evaluate() || mRight -> Evaluate();
}