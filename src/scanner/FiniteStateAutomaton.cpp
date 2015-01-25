#include "Token.h"

Token::Token(string name, Lexeme lexeme, int lineNumber, int columnNumber)
:_lineNumber(lineNumber), _columnNumber(columnNumber), _name(name), _lexeme(lexeme))
{
}