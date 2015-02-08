#include "Token.h"

#include "Lexeme.h"

using namespace std;

Token::Token()
:_lineNumber(-1), _columnNumber(-1)
{
}

Token::Token( Lexeme lexeme, int lineNumber, int columnNumber)
:_lineNumber(lineNumber), _columnNumber(columnNumber), _lexeme(lexeme)
{
}

Token::Token(Lexeme::LexemeType type, string name, int lineNumber, int columnNumber)
	:_lineNumber(lineNumber), _columnNumber(columnNumber), _lexeme(type, name)
{
}

int Token::getColumnNumber()
{
	return _columnNumber;
}

int Token::getLineNumber()
{
	return _lineNumber;
}

Lexeme Token::getLexeme()
{
	return _lexeme;
}

bool Token::hasValidLexeme()
{
	return _lexeme.getType() != Lexeme::MP_INVALID;
}
