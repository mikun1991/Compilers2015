#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "Symbol.h"

#include "Resources.h"

#include <string>
#include <unordered_map>
#include <list>
#include <iostream>

class SymbolTable : public Symbol
{

public:
	SymbolTable(Lexeme lexeme,  LexemeResources::DataType type, int level, SymbolTable* parent = NULL);

	//create a new table and return 
	// a pointer to the child table
	SymbolTable* createTable(Lexeme lexeme, LexemeResources::DataType type);

	//close the current table and return
	// a pointer to the parent table
	SymbolTable* closeTable();

	void insert(Lexeme lex,  LexemeResources::DataType type);

	const Symbol lookup(const std::string name, bool& outFound);

	void printTable();

private:
	int _currentOffset;

	SymbolTable * _parentTable;
	SymbolTable * _activeChildTable;

	std::unordered_map<std::string, Symbol> _symbolLookup;
};


#endif //SYMBOL_TABLE