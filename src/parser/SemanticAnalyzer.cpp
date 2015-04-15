#include "SemanticAnalyzer.h"

//use this to turn on and off comments in the 
//written uMahine code
#define ENABLE_DEBUGGING true

#include <assert.h>

using namespace std;
using namespace LexemeResources;



SemanticAnalyser::SemanticAnalyser()
{
	_currentTable = NULL;
	_outFile.open("compiledUCode.txt");
}

SemanticAnalyser::~SemanticAnalyser()
{
	_outFile.close();
}

bool SemanticAnalyser::createTable(LexemeOperand operand)
{
	LexemeOperand* lexOp = dynamic_cast<LexemeOperand*>(&operand);
	if (lexOp){
		return createTable(lexOp->getLexeme(), lexOp->type());
	}
	return false;
}

bool SemanticAnalyser::createTable(const Lexeme lexeme, DataType type)
{
	//make sure that the table has been initialized
	if (!_currentTable){
		_currentTable = new SymbolTable(lexeme, type, 0);
		return true;
	}

	bool found = false;
	const Symbol match = _currentTable->lookup(lexeme.getValue(), found);

	if (found && 
		(match.lexeme().getValue() != "while" || 
		 match.lexeme().getValue() != "for" ||
		 match.lexeme().getValue() != "if" || match.lexeme().getValue() != "repeat"))

	{//there is already an entry with this name
		symbolCollisionError(Token(lexeme, -1, -1));
		return false;
	}

	_currentTable = _currentTable->createTable(lexeme, type);
	return true;
}

void SemanticAnalyser::closeTable()
{
	SymbolTable* parent = _currentTable->closeTable();
	if (parent){
		_currentTable = parent;
		return;
	}
	else{
		//close the table if it is the last one
		delete _currentTable;
	}
}

bool SemanticAnalyser::insertSymbol(const Token token)
{
	DataType type = UnknownData;

	switch (token.getLexeme().getType())
	{
	case MP_INTEGER:
		type = IntData;
		break;
	case MP_FLOAT:
		type = FloatData;
		break;
	case MP_STRING:
		type = StringData;
	default:
		type = UnknownData;
	}

	//i think we may need to set the type manually for functions/procedures....
	//i am not sure how we will get the reurn type

	return insertSymbol(token, type);
}

bool SemanticAnalyser::insertSymbol(const Token token, DataType type)
{
	if (!_currentTable){
		assert(false);
		return false;//this should not happend;
	}

	bool found;
	const Symbol foundSymbol = _currentTable->lookup(token.getLexeme().getValue(), found);

	if (found){
		symbolCollisionError(token);
		return false;
	}

	_currentTable->insert(token.getLexeme(), type);
	return true;
}

bool SemanticAnalyser::insertSymbol(const Lexeme lex, DataType type)
{
	if (!_currentTable){
		assert(false);
		return false;//this should not happend;
	}

	bool found;
	const Symbol foundSymbol = _currentTable->lookup(lex.getValue(), found);

	if (found){
		symbolCollisionError(Token(lex, -1, -1));
		return false;
	}

	_currentTable->insert(lex, type);
	return true;
}

bool SemanticAnalyser::insertSymbol(SemanticRecord& record)
{
	int numIds = record.size();

	for (int i = 0; i < numIds; i++)
	{
		Operand* next = record.getNextOperandPointer();
		LexemeOperand* nextOp = dynamic_cast<LexemeOperand*>(next);
		assert(nextOp);
		if (nextOp)
			insertSymbol(nextOp->getLexeme(), nextOp->type());
		delete next;

	}

	return true;
}

const Symbol SemanticAnalyser::lookupSymbol(string name, bool& found)
{
	if (!_currentTable){
		assert(false);
		found = false;
		return Symbol();
	}

	return _currentTable->lookup(name, found);
}

string SemanticAnalyser::lookupSymbolAddress(string name, bool& found)
{
	Symbol matchingSymbol = lookupSymbol(name, found);

	if (!found){
		return string();
	}

	char address[64] = { 0 };
	sprintf(address, "%d(D%d)", matchingSymbol.offset(), matchingSymbol.level());
	string addressString(address);

	return addressString;
}

string SemanticAnalyser::stringLitToVal(string value)
{
	return "#" + value;
}

string SemanticAnalyser::intLitToVal(string value)
{
	return "#" + value;
}

string SemanticAnalyser::floatLitToVal(string value)
{
	return "#" + value;
}

string SemanticAnalyser::generateMachineValue(Lexeme lex)
{
	//figure out if we need to look up the value
	//of if the value is a literal and we
	//can pass in the value directly 

	string machineVal;
	bool found = true;
	switch (lex.getType())
	{
	case MP_IDENTIFIER:
	case MP_INTEGER:
	case MP_STRING:
	case MP_FLOAT:
	case MP_BOOLEAN:
		machineVal = lookupSymbolAddress(lex.getValue(), found);
		break;
	case MP_STRING_LIT:
		machineVal = stringLitToVal(lex.getValue());
		break;
	case MP_INTEGER_LIT:
		machineVal = intLitToVal(lex.getValue());
		break;
	case MP_FLOAT_LIT:
		machineVal = floatLitToVal(lex.getValue());
		break;
	default:
		assert(false);
		//this shouldnt happen
		//but i may have missed some
	}

	if (!found){
		missingObject(lex);
	}

	return machineVal;
}

void SemanticAnalyser::missingObject(const Lexeme lex)
{
	string err = "The corresponding symbol was not found for" + lex.getValue() + "\n";
	_errList.push_back(err);
}

void SemanticAnalyser::symbolCollisionError(const Token token)
{
	string err = "This variable has already been used: " + token.getLexeme().getValue() + " \nline:" + to_string(token.getLineNumber()) + " \ncol:" + to_string(token.getColumnNumber()) + "!!.\n";
	_errList.push_back(err);
}

void SemanticAnalyser::printCurrentTable()
{
	if (!_currentTable)
		return;
	_currentTable->printTable();
}

Operand SemanticAnalyser::add(SemanticRecord addRecords)
{
	return twoValueCommand("ADDS", addRecords);
}

Operand SemanticAnalyser::sub(SemanticRecord subractRecords)
{
	return twoValueCommand("SUBS", subractRecords);
}

Operand SemanticAnalyser::multiply(SemanticRecord multiplyRecords)
{
	return twoValueCommand("MULS", multiplyRecords);
}

Operand SemanticAnalyser::divide(SemanticRecord divideRecords)
{
	return twoValueCommand("DIVS", divideRecords);
}

Operand SemanticAnalyser::modulus(SemanticRecord modRecords)
{
	return twoValueCommand("MODS", modRecords);
}

Operand SemanticAnalyser::compGr(SemanticRecord compareRecords)
{
	return twoValueCommand("CMPGTS", compareRecords);
}

Operand SemanticAnalyser::compGrEq(SemanticRecord compareRecords)
{
	return twoValueCommand("CMPGES", compareRecords);
}

Operand SemanticAnalyser::compLt(SemanticRecord compareRecords)
{
	return twoValueCommand("CMPLTS", compareRecords);
}

Operand SemanticAnalyser::compLtEq(SemanticRecord compareRecords)
{
	return twoValueCommand("CMPLES", compareRecords);
}

void SemanticAnalyser::branchIfTrue()
{
	writeCommand("BRTS");
}

void SemanticAnalyser::branchIfFalse()
{
	writeCommand("BRFS");
}

void SemanticAnalyser::prefixCommand(SemanticRecord infixSymbols)
{
	//this should be used for non stack commands like move or compare

	LexemeOperand * first = dynamic_cast<LexemeOperand*>(infixSymbols.getNextOperandPointer());
	assert(first);
	string firstArg = generateMachineValue(first->getLexeme());
	delete first;

	CommandOperand command = infixSymbols.getNextOperandAsCommand();

	string secondArg;
	LexemeOperand* second = NULL;
	if (infixSymbols.size() > 0){
		second = dynamic_cast<LexemeOperand*>(infixSymbols.getNextOperandPointer());
		secondArg = generateMachineValue(second->getLexeme());
	}

	_outFile << command.getCommand() << " " << firstArg << " " << secondArg << " \n";
}



StackOperand SemanticAnalyser::infixStackCommand(SemanticRecord infixSymbols)
{
	assert(infixSymbols.size() == 3);

	//we need to do some sort of type resolution here if the two operands are not
	//the same type, one approach could be to take the smallest common type
	//or to take the type of the first value (current behavior)

	Operand * first = infixSymbols.getNextOperandPointer();
	push(first);

	CommandOperand command = infixSymbols.getNextOperandAsCommand();

	Operand* second = infixSymbols.getNextOperandPointer();
	push(second, first->type());

	writeCommand(command.getCommand());

	StackOperand retVal = StackOperand(command.type() == UnknownData ? first->type() : command.type());
	
	//we own these as soon as the are take from the SemanticRecord
	//delete them now that we are done 
	delete first;
	delete second;

	return retVal;
}

Operand SemanticAnalyser::twoValueCommand(const string command, SemanticRecord records)
{
	assert(records.size() == 2);

	//we need to do some sort of type resolution here if the two operands are not
	//the same type, one approach could be to take the smallest common type
	//or to take the type of the first value (current behavior)

	Operand * first = records.getNextOperandPointer();
	push(first);
	DataType typeOfOp = first->type();

	Operand* second = records.getNextOperandPointer();
	push(second, typeOfOp);

	writeCommand(command);


	delete first;
	delete second;

	return StackOperand(typeOfOp);
}

void SemanticAnalyser::push(Operand* val, DataType castType)
{
	if (!val->onTopOfStack())
	{

		//then this should be on the top of the stack
		//and it doesnt need to be pushed
		LexemeOperand* lexOp = dynamic_cast<LexemeOperand*>(val);
		assert(lexOp);
		string valAddress = generateMachineValue(lexOp->getLexeme());
		_outFile << "PUSH " << valAddress;

		if (ENABLE_DEBUGGING && !val->getName().empty()){
			//add comment with the variable name after the push 
			_outFile << " ;" << val->getName() << std::endl;
		}

		_outFile << std::endl;
	}
	if (castType != UnknownData){
		cast(val->type(), castType);
	}
}

void SemanticAnalyser::cast(const DataType valType,const DataType toType)
{
	if (valType == toType){
		return; //already the correct type
	}

	if (valType == IntData && toType == FloatData){
		writeCommand("CASTSF");
		return;
	}

	if (valType == FloatData && toType == IntData){
		writeCommand("CASTSI");
		return;
	}

	assert(false);
	//we should not be casting other type
	return;
}

void SemanticAnalyser::writeCommand(const string command)
{
	_outFile << command << std::endl;
}