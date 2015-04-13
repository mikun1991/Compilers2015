#include "SemanticRecord.h"

using namespace LexemeResources;
using namespace std;


void SemanticRecord::addOperand(Lexeme id, DataType type)
{
	_identifiers.push_back(LexemeOperand(id, type));
}

Operand SemanticRecord::getNextOperand()
{
	Operand nextOp;

	if (!_identifiers.empty()){
		nextOp = _identifiers.front();
		_identifiers.pop_front();
	}

	return nextOp;
}

Operand SemanticRecord::showNextOperand()
{
	Operand nextOp;

	if (!_identifiers.empty()){
		nextOp = _identifiers.front();
		_identifiers.pop_front();
	}

	return nextOp;
}

int SemanticRecord::size() const
{
	return _identifiers.size();
}


void SemanticRecord::setType(DataType type)
{ 
	//need to iterate through the list and reset all of the types
}
