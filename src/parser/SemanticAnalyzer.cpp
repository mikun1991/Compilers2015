#include "SemanticAnalyzer.h"

#include <assert.h>

using namespace std;
using namespace LexemeResources;

SemanticAnalyser::SemanticAnalyser()
{
	_currentTable = NULL;
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
	if (found){
		//there is already an entry with this name
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

const Symbol SemanticAnalyser::lookupSymbol(string name, bool& found)
{
	if (!_currentTable){
		assert(false);
		found = false;
		return Symbol();
	}

	return _currentTable->lookup(name, found);
}


void SemanticAnalyser::symbolCollisionError(const Token token)
{
	string err = "This variable has already been used: " + token.getLexeme().getValue() + " \nline:" + to_string(token.getLineNumber()) + " \ncol:" + to_string(token.getColumnNumber())+"!!.\n";
	_errList.push_back(err);
}

void SemanticAnalyser::printCurrentTable()
{
	_currentTable->printTable();
}

