#ifndef SEMANTICRECORD_H
#define SEMANTICRECORD_H


#include "Resources.h"
#include "Token.h"
#include "Lexeme.h"
#include "Operand.h"

#include <list>

class SemanticRecord{

public:
	void addOperand(Lexeme id, LexemeResources::DataType type = LexemeResources::UnknownData);
	void addOPerand(Operand operand);

	Operand getNextOperand();
	LexemeOperand getNextOperandAsLexeme();

	Operand showNextOperand(); // use this to return the first value but keep it in the list of Ids
	LexemeResources::DataType getType();

	int size() const;

	void setType(LexemeResources::DataType type);

private:
	std::list<Operand*> _identifiers;
};


#endif //SEMANTICRECORD_H