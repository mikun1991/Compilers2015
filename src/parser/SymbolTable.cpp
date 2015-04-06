#include "SymbolTable.h"

#include "Symbol.h"

#include "Resources.h"


using namespace std;
using namespace LexemeResources;


SymbolTable::SymbolTable(Lexeme lexeme, LexemeResources::DataType type, int level, SymbolTable* parent)
	:Symbol(lexeme, type, level)
{
	_currentOffset = 0; //TODO: should change this if the type has a return value
	_parentTable = parent;
	_activeChildTable = NULL;
}

SymbolTable* SymbolTable::createTable(Lexeme lexeme, LexemeResources::DataType type)
{
	int childLevel = _level + 1;
	SymbolTable* childTable = new SymbolTable(lexeme, type, childLevel, this);
	
	return childTable;
}

SymbolTable* SymbolTable::closeTable()
{
	///size the size of the symbol table so this 
	//symbol will have the correct size
	//when it is refered to

	_size = 0;
	unordered_map<string, Symbol>::const_iterator symbolIt = _symbolLookup.begin();
	while (symbolIt != _symbolLookup.end()){
		_size += symbolIt->second.size();
		symbolIt++;
	}

	//clear the current entries in the table
	_symbolLookup.clear();

	return _parentTable;
}

void SymbolTable::insert(Lexeme lex,  DataType type)
{
	//size is always 1 right?!?
	int size = 1;
	Symbol newSymbol(lex, type, _level, _currentOffset, size);
	_currentOffset += size;

	_symbolLookup[lex.getValue()] =  newSymbol;
}

const Symbol SymbolTable::lookup(const string name, bool& outFound)
{
	outFound = true;
	try{
		return _symbolLookup.at(name);
	}
	catch(out_of_range){
		outFound = false;
		if (_parentTable){
			//if it wasnt found at this nesting level
			//check the parent table to see if 
			//it is defined there
			return _parentTable->lookup(name, outFound);
		}
		else{
			return Symbol();
		}
	}
}

void SymbolTable::printTable()
{
	std::cout
		<< "\nCurrent Table Name: " << lexeme().getValue()
		<< "\nCurrent Table Level: " << level()
		<< "\nCurrent Table Size : " << size()
		<< "\nCurrent Table Offset: " << offset()
		<< "\n";

	std::cout << "\nSymbol Name:\tDataType: \tOffset: \n";

	for (auto& x : _symbolLookup)
		std::cout << x.first << "\t\t" << x.second.dataType() << "\t\t" << x.second.offset() << "\t\t" << std::endl;
}