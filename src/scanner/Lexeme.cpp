#include "Lexeme.h"

Lexeme::Lexeme(Type type, string value)
	:_type(type), _value(value)
{
}

Lexeme::Type Lexeme::getType()
{
	return _type;
}

string Lexeme::getValue()
{
	return _value;
}