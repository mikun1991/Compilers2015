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
	_labelCounter = 0;
}

SemanticAnalyser::~SemanticAnalyser()
{
    _outFile.flush();
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

string SemanticAnalyser::lookupSymbolAddress(string name, bool& found, DataType& outType)
{
	Symbol matchingSymbol = lookupSymbol(name, found);
	outType = matchingSymbol.dataType();

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
	return "#\"" + value + "\"";
}

string SemanticAnalyser::intLitToVal(string value)
{
	return "#" + value;
}

string SemanticAnalyser::floatLitToVal(string value)
{
	return "#" + value;
}

MachineVal SemanticAnalyser::generateMachineValue(Lexeme lex)
{
	//figure out if we need to look up the value
	//of if the value is a literal and we
	//can pass in the value directly 

	DataType type;
	string machineVal;
	bool found = true;
	switch (lex.getType())
	{
	case MP_IDENTIFIER:
	case MP_INTEGER:
	case MP_STRING:
	case MP_FLOAT:
	case MP_BOOLEAN:
		machineVal = lookupSymbolAddress(lex.getValue(), found, type);
		break;
	case MP_STRING_LIT:
		type = StringData;
		machineVal = stringLitToVal(lex.getValue());
		break;
	case MP_INTEGER_LIT:
		type = IntData;
		machineVal = intLitToVal(lex.getValue());
		break;
	case MP_FLOAT_LIT:
		type = FloatData;
		machineVal = floatLitToVal(lex.getValue());
		break;
    case MP_TRUE:
        type = BoolData;
        machineVal = "#1";
        break;
    case MP_FALSE:
        type = BoolData;
        machineVal = "#0";
        break;
	default:
		assert(false);
		//this shouldnt happen
		//but i may have missed some
	}

	if (!found){
		missingObject(lex);
	}

	return MachineVal(machineVal, type);
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

void SemanticAnalyser::programHeading()
{
	int memAlloc = _currentTable->size();
	
	_outFile << "MOV SP D0" << "\n";
	_outFile << "PUSH SP" << "\n";
	_outFile << "PUSH #" <<to_string(memAlloc) <<" \n";
	_outFile << "ADDS" << "\n";
	_outFile << "POP SP" << "\n";
}

void SemanticAnalyser::programTail()
{
	//deallocate and Halt!!!
	_outFile << "MOV D0 SP" << " \n";
	_outFile << "HLT" << " \n";
}

void SemanticAnalyser::ifStatementBegin(int& nextLabel)
{
	//if not true then branch to the next 
	//label, which should be the else or
	//the end of the if statement
	nextLabel = getNextLabelVal();
	_outFile << "BRFS L" << nextLabel  << " \n";

}

void SemanticAnalyser::ifStatementElse(int currentLabel, int&nextLabel)
{
	//end of true section jump to the end 
	nextLabel = getNextLabelVal();
	_outFile << "L" << nextLabel << ":\n";

	//the if was false start here 
	_outFile << "L" << currentLabel << ":\n";

}

void SemanticAnalyser::ifStatementEnd(int currentLabel)
{
	_outFile << "L" << currentLabel << ":\n";
}

void SemanticAnalyser::whileStatementPrecondition(int& repeatLabel)
{
	repeatLabel = getNextLabelVal();
	_outFile << "L" << repeatLabel << ":\n";
}

void SemanticAnalyser::whileStatementPostcondition(int& exitLabel)
{
	//if false exit
	_outFile << "BRFS L" << exitLabel << ":\n";

	exitLabel = getNextLabelVal();
	_outFile << "L" << exitLabel << ":\n";
}

void SemanticAnalyser::whileStatementPostbody(int repeatLabel, int exitLabel)
{
	_outFile << "BR L" << repeatLabel << " \n";
	_outFile << "L:" << exitLabel << "\n";
}

void SemanticAnalyser::writeList(SemanticRecord& writeSymbols, bool writeLn)
{
	while (writeSymbols.size()){
		Operand * nextOp = writeSymbols.getNextOperandPointer();
		push(nextOp);
		delete nextOp;
		_outFile << "WRTS " << " \n";
	}
	//TODO: this could be optimized to be inlcuded as the last command in the loop
	if (writeLn){
		_outFile << "WRTLN" << " \n";
	}
}

void SemanticAnalyser::repeatBegin(int& beginLabel)
{
	beginLabel = getNextLabelVal();
	_outFile << "L:" << beginLabel << "\n";
}

void SemanticAnalyser::repeatExit(int repeatLabel)
{
	_outFile << "BRTS L" << repeatLabel << "\n";
}

void SemanticAnalyser::forBegin(int& beginCondition, SemanticRecord controlVars)
{
	//we need to allocate the space for the variables
	int level = _currentTable->level() + 1;
	
	int controlVals = 3;// one for control variable,step val, and one for the final value
	_outFile << "MOV SP D"<< level << "\n";
	_outFile << "PUSH SP" << "\n";
	_outFile << "PUSH #" << to_string( controlVals ) << " \n";
	_outFile << "ADDS" << "\n";
	_outFile << "POP SP" << "\n";
	//we have created the space now we need to copy the input values into position
	


	LexemeOperand lexOp2 = controlVars.getNextOperandAsLexeme();
	MachineVal initVal = generateMachineValue(lexOp2.getLexeme());
	LexemeOperand lexOp1 = controlVars.getNextOperandAsLexeme();
	MachineVal controlVal = generateMachineValue(lexOp1.getLexeme());
	LexemeOperand lexOp3 = controlVars.getNextOperandAsLexeme();
	MachineVal finalVal = generateMachineValue(lexOp3.getLexeme());

	_outFile << "MOV " << controlVal.value << " 0(D" << level << ") " << "\n";
	_outFile << "MOV " << initVal.value << " 1(D" << level << ") " << "\n";
	_outFile << "MOV " << finalVal.value << " 2(D" << level << ") " << "\n";

	controlVal.value = " 0(D" + to_string(level) + ") ";
	initVal.value = " 1(D" + to_string(level) + ") ";
	finalVal.value = " 2(D" + to_string(level) + ") ";
	
	//copied values into alocated memory

	//start the contitional 
	//if control is less than zero 


	_outFile << "ADD " << controlVal.value << " " << initVal.value << " " << initVal.value <<" \n";


}

void SemanticAnalyser::forEndCondition(int& exitLoop)
{
	//the condition has been checked branch if false
}

void SemanticAnalyser::forEndBody(int exitLoop)
{

}

void SemanticAnalyser::unaryPrefixCommand(SemanticRecord& infixSymbols)
{
	assert(infixSymbols.size() == 2);

	LexemeOperand * first = dynamic_cast<LexemeOperand*>(infixSymbols.getNextOperandPointer());
	assert(first);
	MachineVal firstArg = generateMachineValue(first->getLexeme());
	delete first;

	CommandOperand command = infixSymbols.getNextOperandAsCommand();

	//MachineVal secondArg;
	//LexemeOperand* second = NULL;
	//if (infixSymbols.size() > 0){
	//	second = dynamic_cast<LexemeOperand*>(infixSymbols.getNextOperandPointer());
	//	if (second)
	//		secondArg = generateMachineValue(second->getLexeme());
	//}

	_outFile << command.getCommand()  << " " << firstArg.value << " \n";
}

StackOperand SemanticAnalyser::infixStackCommand(SemanticRecord& infixSymbols)
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

StackOperand SemanticAnalyser::push(Lexeme lex, DataType type)
{
	LexemeOperand * lexOp = new LexemeOperand(lex, UnknownData);

	push(lexOp);
	StackOperand retVal(lexOp->type());

	delete lexOp;
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
		MachineVal valAddress = generateMachineValue(lexOp->getLexeme());

		//I dont like this but it is a way to pass the
		//type back up
		val->setType(valAddress.type);

		if (ENABLE_DEBUGGING && !val->getName().empty()){
			//add comment with the variable name before the push 
			_outFile << ";\t\tPushing: " << val->getName() << "\n";
		}

		_outFile << "PUSH " << valAddress.value << " \n";

	}
	if (castType != UnknownData){
		cast(val->type(), castType);
	}
    _outFile.flush();
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
	_outFile << command << "\n\n";
}

int SemanticAnalyser::getNextLabelVal()
{
	return _labelCounter++;
}