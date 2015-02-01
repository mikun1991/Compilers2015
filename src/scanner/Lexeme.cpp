#include "Lexeme.h"


Lexeme::Lexeme()
	:_type(Lexeme::Invalid), _value("")
{
}

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

string Lexeme:typeToName(Type type)
{
	return TypeNames[type];
}
