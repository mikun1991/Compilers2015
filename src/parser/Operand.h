#ifndef OPERAND_H
#define OPERAND_H

#include "Resources.h"
#include "Token.h"

#include <string>

class Operand
{

private:
	Operand();

public:
	bool onTopOfStack();
	std::string address();
	LexemeResources::DataType type();

private:
	LexemeResources::DataType _dataType;
	std::string _address;
};


class TokenOperand : public Operand
{
public:
	TokenOperand(const Token token);

private:
	const Token _token; //probably dont need to save this

};

class CompoundOperand : public Operand
{
public:
	CompoundOperand(std::string address, LexemeResources::DataType type);

private:


};



#endif // !OPERAND_H
