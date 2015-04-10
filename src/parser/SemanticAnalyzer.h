#ifndef SEMANTICANALYSER_H
#define SEMANTICANALYSER_H

#include "Resources.h"
#include "Token.h"
#include "Symbol.h"
#include "SymbolTable.h"

#include "Operand.h"
#include "SemanticRecord.h"

#include <iostream>
#include <fstream>

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
	std::string lookupSymbolAddress(std::string name, bool& found);
	
	std::string stringLitToVal(std::string value);
	std::string intLitToVal(std::string value);
	std::string floatLitToVal(std::string value);
	
	std::string generateMachineValue(Lexeme lex);


	void printCurrentTable();
	std::string errorMsg();

	//These are the commands that we can call from the parser
	//with the semantic records to generate that code 
	void assignment(SemanticRecord assigmentRecords);

	void add(SemanticRecord addRecords);
	void sub(SemanticRecord subtractRecords);
	void multiply(SemanticRecord multiplyRecords);
	void divide(SemanticRecord divideRecords);
	void modulus(SemanticRecord modRecords);


	void compGr(SemanticRecord compareRecords);
	void compGrEq(SemanticRecord compareRecords);
	void compLt(SemanticRecord compareRecords);
	void compLtEq(SemanticRecord compareRecords);

	void branchIfTrue();
	void branchIfFalse();


private:
	//these are some helper functions so i can be lazy in creating
	//the functions for writing command
	void twoValueCommand(std::string command, SemanticRecord records);

	//if we have methods which call the uMachine instructions
	//we can be sneeky and add comments which describe the 
	//value that we are working with, this will make 
	//debugging the uMachine code alot easier.
	void push(Lexeme val);
	void writeCommand(std::string command);


	//file pointer
	std::ofstream _outFile;

	//////////////
	//fun ways to generate errors
	
	//for missing objects
	void missingObject(const Lexeme lex);

	//for namespace collisions
	void symbolCollisionError(const Token lex);
	std::list<std::string> _errList;
	
	SymbolTable * _currentTable;
};



#endif //SEMANTICANALYSER_H