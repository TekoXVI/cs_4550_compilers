void main() {
	SymbolTableClass symbolTable;
	
	// IntegerNode* in = new IntegerNode(3);
	IdentifierNode* in = new IdentifierNode("sum", &symbolTable);
	CoutStatementNode* csn = new CoutStatementNode(in);
	StatementGroupNode* sgn = new StatementGroupNode();
	sgn -> AddStatement(csn);
	BlockNode* bn = new BlockNode(sgn);
	ProgramNode* pn = new ProgramNode(bn);
	StartrNode* sn = new StartrNode(pn);
	
	delete sn;
	
	// sn -> Interpret();
	
	// sn -> Code();
	// sn -> Execute();
}