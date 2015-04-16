#ifndef SEMANTICRECORD_H
#define SEMANTICRECORD_H


#include "Resources.h"
#include "Token.h"
#include "Lexeme.h"
#include "Operand.h"

#include <list>

class SemanticRecord{

public:
	~SemanticRecord();

	void addOperand(Lexeme id, LexemeResources::DataType type = LexemeResources::UnknownData);
	void addOperand(CommandOperand operand);
	void addOperand(StackOperand operand);
	void addOperand(Operand* operand);

	Operand* getNextOperandPointer();
	Operand getNextOperand();
	LexemeOperand getNextOperandAsLexeme();
	CommandOperand getNextOperandAsCommand();

	Operand showNextOperand(); // use this to return the first value but keep it in the list of Ids
	LexemeResources::DataType getType();

	int size() const;

	void setType(LexemeResources::DataType type);

private:
	std::list<Operand*> _identifiers;
};


#endif //SEMANTICRECORD_H