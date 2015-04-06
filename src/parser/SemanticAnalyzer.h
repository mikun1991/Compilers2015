#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "Resources.h"
#include "Token.h"
#include "Symbol.h"
#include "SymbolTable.h"
<<<<<<< HEAD
#include "Operand.h"
=======
#include "SemanticRecord.h"

>>>>>>> origin/master

//this class will keep track of 
//the current instance of the symbol table
//as well as current semantic actions
class SemanticAnalyser
{

public:
	SemanticAnalyser();

	//return false if there was a name collision
	
	bool createTable(const Token token, LexemeResources::DataType type);
	void closeTable();

	//i think we should be able to figure out the type from the 
	//the lexeme (at least some of the time)
	bool insertSymbol(const Token token);
	bool insertSymbol(const Token token, LexemeResources::DataType type);
	bool insertSymbol(SemanticRecord& record);
	const Symbol lookupSymbol(std::string name, bool& found);

	std::string errorMsg();

<<<<<<< HEAD

	void defineInt();
	void defineFloat();
	void defineString();

	void add();
	void sub();
	void multiply();
	void divide();
	void modulus();

=======
	void printCurrentTable();
>>>>>>> origin/master

private:

	//for namespace collisions
	void symbolCollisionError(const Token lex);
	std::list<std::string> _errList;
	
	SymbolTable * _currentTable;
};



#endif //SEMANTICANALYSER_H