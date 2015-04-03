#include "SemanticRecord.h"

using namespace LexemeResources;
using namespace std;

void SemanticRecord::addId(Token id)
{
	_identifiers.push_back(id);
}

void SemanticRecord::setType(DataType type)
{
	_type = type;
}

Token SemanticRecord::getNextId()
{
	Token myToken;

	if (!_identifiers.empty()){
		myToken = _identifiers.front();
		_identifiers.pop_front();
	}

	return myToken;
}

DataType SemanticRecord::getType()
{
	return _type;
}