#include "SemanticRecord.h"

using namespace LexemeResources;
using namespace std;

void SemanticRecord::addId(Lexeme id)
{
	Token newToken;
	newToken.setLexeme(id);
	_identifiers.push_back(newToken);
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