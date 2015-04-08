#include "SemanticAnalyzer.h"

#include <assert.h>

using namespace std;
using namespace LexemeResources;

SemanticAnalyser::SemanticAnalyser()
{
	_currentTable = NULL;
	_outFile.open("compiledUCode.txt");
}

bool SemanticAnalyser::createTable(const Token token, DataType type)
{
	//make sure that the table has been initialized
	if (!_currentTable){
		_currentTable = new SymbolTable(token.getLexeme(), type, 0);
		return true;
	}

	bool found = false;
	const Symbol match = _currentTable->lookup(token.getLexeme().getValue(), found);

	if (found && 
		(match.lexeme().getValue() != "while" || 
		 match.lexeme().getValue() != "for" ||
		 match.lexeme().getValue() != "if" || match.lexeme().getValue() != "repeat"))

	{//there is already an entry with this name
		symbolCollisionError(token);
		return false;
	}

	_currentTable = _currentTable->createTable(token.getLexeme(), type);
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

bool SemanticAnalyser::insertSymbol(SemanticRecord& record)
{
	int numIds = record.size();

	for (int i = 0; i < numIds; i++)
	{
		insertSymbol(record.getNextId(), record.getType());
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


void SemanticAnalyser::symbolCollisionError(const Token token)
{
	string err = "This variable has already been used: " + token.getLexeme().getValue() + " \nline:" + to_string(token.getLineNumber()) + " \ncol:" + to_string(token.getColumnNumber())+"!!.\n";
	_errList.push_back(err);
}

void SemanticAnalyser::printCurrentTable()
{
	if (!_currentTable)
		return;
	_currentTable->printTable();
}

void SemanticAnalyser::add(SemanticRecord addRecords)
{
	assert(addRecords.size() == 2);

	Token first = addRecords.getNextId();


	//addressFirst = lookupSymbolAddress(addRecords.getNextId());


}

void SemanticAnalyser::sub(SemanticRecord subractRecords)
{

}

void SemanticAnalyser::multiply(SemanticRecord multiplyRecords)
{


}

void SemanticAnalyser::divide(SemanticRecord divideRecords)
{

}

void SemanticAnalyser::modulus(SemanticRecord modRecords)
{

}

void SemanticAnalyser::compGr(SemanticRecord compareRecords)
{

}

void SemanticAnalyser::compGrEq(SemanticRecord compareRecords)
{

}

void SemanticAnalyser::compLt(SemanticRecord compareRecords)
{

}

void SemanticAnalyser::compLtEq(SemanticRecord compareRecords)
{

}

void SemanticAnalyser::branchIfTrue()
{

}


