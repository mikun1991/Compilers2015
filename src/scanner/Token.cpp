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

Lexeme Token::getLexeme()
{
	return _lexeme;
}
