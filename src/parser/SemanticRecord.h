#ifndef SEMANTICRECORD_H
#define SEMANTICRECORD_H

#include "Resources.h"
#include "Token.h"
#include "Lexeme.h"

#include <list>

class SemanticRecord{

public:
	void addId(Lexeme);
	void setType(LexemeResources::DataType);

	Token getNextId();
	LexemeResources::DataType getType();

private:
	std::list<Token> _identifiers;
	LexemeResources::DataType _type;

};

#endif //SEMANTICRECORD_H