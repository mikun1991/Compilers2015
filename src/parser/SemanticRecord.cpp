#include "SemanticRecord.h"

#include <assert.h>

using namespace LexemeResources;
using namespace std;


SemanticRecord::~SemanticRecord()
{
	while (_identifiers.size()){
		delete _identifiers.front();
		_identifiers.pop_front();
	}
}

void SemanticRecord::addOperand(Lexeme id, DataType type)
{
	LexemeOperand * addOP = new LexemeOperand(id, type);
	_identifiers.push_back(addOP);
}

void SemanticRecord::addOperand(CommandOperand operand)
{
	CommandOperand* cmdOp = new CommandOperand(operand);
	_identifiers.push_back(cmdOp);
}

void SemanticRecord::addOperand(StackOperand operand)
{
	StackOperand* stkOp = new StackOperand(operand);
	_identifiers.push_back(stkOp);

}

void SemanticRecord::addOperand(Operand* operand)
{
	_identifiers.push_back(operand);
}

Operand* SemanticRecord::getNextOperandPointer()
{
	Operand* nextOp = NULL;

	if (!_identifiers.empty()){
		nextOp = _identifiers.front();
		_identifiers.pop_front();
	}

	return nextOp;
}

Operand SemanticRecord::getNextOperand()
{
	Operand* nextOp = NULL;

	if (!_identifiers.empty()){
		nextOp = _identifiers.front();
		_identifiers.pop_front();
	}
	assert(nextOp);

	return *nextOp;
}

LexemeOperand SemanticRecord::getNextOperandAsLexeme()
{
	LexemeOperand* nextOp = NULL;

	if (!_identifiers.empty()){
		nextOp = dynamic_cast<LexemeOperand*>( _identifiers.front());
		_identifiers.pop_front();
	}
	assert(nextOp);

	if (nextOp)
		return *nextOp;

	return LexemeOperand(Lexeme(), UnknownData);
}

CommandOperand SemanticRecord::getNextOperandAsCommand()
{
	CommandOperand* nextOp = NULL;

	if (!_identifiers.empty()){
		nextOp = dynamic_cast<CommandOperand*>(_identifiers.front());
		_identifiers.pop_front();
	}
	assert(nextOp);

	if (nextOp)
		return *nextOp;
	
	return CommandOperand("", UnknownData);
}


Operand SemanticRecord::showNextOperand()
{
	Operand* nextOp;

	if (!_identifiers.empty()){
		nextOp = _identifiers.front();
	}

	// we still own this
	return Operand(*nextOp);
}

int SemanticRecord::size() const
{
	return _identifiers.size();
}


void SemanticRecord::setType(DataType type)
{ 
	//need to iterate through the list and reset all of the types

	std::list<Operand*>::const_iterator iterator;
	for (iterator = _identifiers.begin(); iterator != _identifiers.end(); ++iterator) {
		Operand* myOP = *iterator;
		myOP->setType(type);
	}
}
