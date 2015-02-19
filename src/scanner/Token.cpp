#include "Token.h"

#include "Lexeme.h"

using namespace std;
using namespace LexemeResources;

Token::Token()
	:_lineNumber(-1), _columnNumber(-1)
{
}

Token::Token(Lexeme lexeme, int lineNumber, int columnNumber)
	: _lineNumber(lineNumber), _columnNumber(columnNumber), _lexeme(lexeme)
{
}

Token::Token(LexemeType type, string name, int lineNumber, int columnNumber)
	: _lineNumber(lineNumber), _columnNumber(columnNumber), _lexeme(type, name)
{
}

void Token::setLexeme(Lexeme newLexeme)
{
	_lexeme = newLexeme;
}

int Token::getColumnNumber() const
{
	return _columnNumber;
}

int Token::getLineNumber() const
{
	return _lineNumber;
}

Lexeme Token::getLexeme() const
{
	return _lexeme;
}

bool Token::hasValidLexeme() const
{
	return _lexeme.getType() != LexemeType::MP_INVALID;
}

LexemeType Token::getType() const
{
	return _lexeme.getType();
}
