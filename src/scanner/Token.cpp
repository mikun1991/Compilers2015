#include "Token.h"


Token::Token()
:_lineNumber(-1), _columnNumber(-1)
{
}

Token::Token( Lexeme lexeme, int lineNumber, int columnNumber)
:_lineNumber(lineNumber), _columnNumber(columnNumber), _lexeme(lexeme)
{
}

Lexeme Token::getLexeme()
{
	return _lexeme;
}
