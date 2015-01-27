#include "Token.h"


Token::Token()
:_lineNumber(-1), _columnNumber(-1),
{
}

Token::Token(string name, Lexeme lexeme, int lineNumber, int columnNumber)
:_lineNumber(lineNumber), _columnNumber(columnNumber), _name(name), _lexeme(lexeme)
{
}

