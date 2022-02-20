#include "Symbol.cpp"
#include <iostream>

int main() {
	SymbolTableClass table;
	std::cout << table.Exists("something");
	table.AddEntry("meow");
	std::cout << table.GetValue("meow") << std::endl;
	return 0;
}