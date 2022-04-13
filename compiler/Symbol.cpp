#include "Symbol.h"

SymbolTableClass::SymbolTableClass() {
	
}

bool SymbolTableClass::Exists(const std::string & s) { 
// returns true if <s> is already in the symbol table.
	for(unsigned int i=0; i<mTable.size(); i++) {
		if (mTable[i].mLabel == s) {
			return true;	
		}
	}
	return false;
} 

void SymbolTableClass::AddEntry(const std::string & s) { 
// adds <s> to the symbol table, 
// or quits if it was already there
	if (!Exists(s)) {
		Variable v;
		v.mLabel = s;
		v.mValue = 0;
		mTable.push_back(v);
	} else {
		exit(1);
	}
} 
int SymbolTableClass::GetValue(const std::string & s) { 
// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
	if (Exists(s)) {
		int i = GetIndex(s);
		// std::cout << "Label: " << mTable[i].mLabel << ", value: " << mTable[i].mValue << std::endl;
		return mTable[i].mValue;
	} else {
		std::cout << "'" << s << "' does not exist." << std::endl;
		exit(1);
	}
} 

void SymbolTableClass::SetValue(const std::string & s, int v) { 
// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
	if (Exists(s)) {
		int i = GetIndex(s);
		mTable[i].mValue = v;
	} else {
		std::cout << s << " does not exist." << std::endl;
		exit(1);
	}
} 

int SymbolTableClass::GetIndex(const std::string & s) { 
// returns the index of where variable <s> is.
// returns -1 if variable <s> is not there.
	for(unsigned int i=0; i<mTable.size(); i++) {
		if (mTable[i].mLabel == s) {
			return i;	
		}
	}
	return -1;
}

int SymbolTableClass::GetCount() { 
// returns the current number of variables in the symbol
// table.
	return mTable.size();
} 
