#include "Lexeme.h"

using namespace LexemeResources;
using namespace std;

Lexeme::Lexeme() :
_type(MP_INVALID), _value("")
{

}

Lexeme::Lexeme(LexemeType type, string value) :
_type(type), _value(value)
{
}

LexemeType Lexeme::getType() const
{
	return _type;
}

string Lexeme::getValue() const
{
	return _value;
}

string Lexeme::typeToName() const
{
	return LexemeNames[(int)_type];
}
