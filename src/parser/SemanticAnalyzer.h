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


struct MachineVal
{
	MachineVal(std::string inValue = "", LexemeResources::DataType inType = LexemeResources::UnknownData)
		:type(inType), value(inValue)
	{
		value = inValue;
		type = inType;
	}

	std::string value; //address or literal value
	LexemeResources::DataType type;
};

//this class will keep track of 
//the current instance of the symbol table
//as well as current semantic actions
class SemanticAnalyser
{

public:
	SemanticAnalyser();
	~SemanticAnalyser();

	//return false if there was a name collision
	bool createTable(LexemeOperand operand);
	bool createTable(const Lexeme token, LexemeResources::DataType type);
	void closeTable();

	//i think we should be able to figure out the type from the 
	//the lexeme (at least some of the time)
	bool insertSymbol(const Token token);
	bool insertSymbol(const Token token, LexemeResources::DataType type);
	bool insertSymbol(const Lexeme lex, LexemeResources::DataType type);
	bool insertSymbol(SemanticRecord& record);


	const Symbol lookupSymbol(std::string name, bool& found);
	std::string lookupSymbolAddress(std::string name, bool& found, LexemeResources::DataType& outType);
	
	std::string stringLitToVal(std::string value);
	std::string intLitToVal(std::string value);
	std::string floatLitToVal(std::string value);
	
	LexemeResources::DataType checkType(LexemeOperand* operand);
	MachineVal generateMachineValue(Lexeme lex);


	void printCurrentTable();
	std::string errorMsg();


	void programHeading();
	void programTail();

	//call this after the booleanExpression has
	//been evaluated and is on top of the stack
	void ifStatementBegin(int& nextLabel);
	void ifStatementElse(int currentLabel, int& exitLabel);
	void ifStatementEnd(int lastLabel);

	//while statement
	void whileStatementPrecondition(int& repeatLabel);
	void whileStatementPostcondition(int& endLabel);
	void whileStatementPostbody(int repeatLabel, int exitLoop);

	//repeat statement
	void repeatBegin(int& repeatStart);
	void repeatExit(int repeatStart);

	//for statement
	void forBegin(int& beginCondition, SemanticRecord controlVars);
	void forEndCondition(int& exitLoop);
	void forEndBody(int exitLoop);

	void writeList(SemanticRecord& writeSymbols, bool writeLn = true);

	//The command is in the form
	//[Command] [Argument] 
	void unaryPrefixCommand(SemanticRecord& infixSymbols);
	


	//The command are in the order they are encountered
	//ie A + B 
	// Operand Command Operand
	StackOperand infixStackCommand(SemanticRecord& infixSymbols);

	StackOperand push(Lexeme lex, LexemeResources::DataType type = LexemeResources::UnknownData);

	void writeCommand(const std::string command);

private:
	//these are some helper functions so i can be lazy in creating
	//the functions for writing command
	Operand twoValueCommand(const std::string command, SemanticRecord records);

	//if we have methods which call the uMachine instructions
	//we can be sneeky and add comments which describe the 
	//value that we are working with, this will make 
	//debugging the uMachine code alot easier.
	void push(Operand* val, const LexemeResources::DataType castType = LexemeResources::UnknownData);
	void cast(const LexemeResources::DataType valType, const LexemeResources::DataType toType);
	

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

	int getNextLabelVal();
	int _labelCounter;
};



#endif //SEMANTICANALYSER_H