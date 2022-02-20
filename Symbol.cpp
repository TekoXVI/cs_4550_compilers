#include "Symbol.h"

SymbolTableClass::SymbolTableClass()
	: mTable() {
	
}

bool SymbolTableClass::Exists(const std::string & s) { 
// returns true if <s> is already in the symbol table.
	Variable S = s;
	if (std::find(mTable.begin(), mTable.end(), s) != mTable.end()) {
		return true;
	} else {
		return false;
	}
} 

void SymbolTableClass::AddEntry(const std::string & s) { 
// adds <s> to the symbol table, 
// or quits if it was already there
	if (!Exists(s)) {
		mTable.push_back(s);
	} else {
		exit(1);
	}
} 
int SymbolTableClass::GetValue(const std::string & s) { 
// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
	if (Exists(s)) {
		return mTable[s].mValue;
	} else {
		std::cout << s << " does not exist." << std::endl;
		exit(1);
	}
} 

void SymbolTableClass::SetValue(const std::string & s, int v) { 
// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
	if (Exists(s)) {
		mTable[s.mValue] = v;
	} else {
		std::cout << s << " does not exist." << std::endl;
		exit(1);
	}
} 

int SymbolTableClass::GetIndex(const std::string & s) { 
// returns the index of where variable <s> is.
// returns -1 if variable <s> is not there.
	auto it = find(mTable.begin(), mTable.end(), s);
	if (it != mTable.end()) {
		int index = it - mTable.begin();
		return index;
	} else {
		return -1;
	}
} 

int SymbolTableClass::GetCount() { 
// returns the current number of variables in the symbol
// table.
	return mTable.size();
} 
