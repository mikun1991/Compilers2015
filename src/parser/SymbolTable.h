#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "Symbol.h"

#include <string>
#include <hash_map>
#include <list>

class SymbolTable : public Symbol
{

public:
	SymbolTable();
	~SymbolTable();

	void createSubTable();
	bool collapseSubTable();

	void insert(Symbol newSymbol);
	Symbol lookup(std::string name );

	Symbol attributes();



private:
	//type
	
	//Lexemes and their attributes
	std::list<Symbol> symbolList;

	std::hash_map<std::string, int> _symbolLookup;
};


#endif //SYMBOL_TABLE