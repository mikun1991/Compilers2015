#ifndef TOKEN_H
#define TOKEN_H

#include "Lexeme.h"


class Token {
    
    
public:

	Token ();
	Token(Lexeme::LexemeType type, std::string name , int lineNumber, int columnNumber);
	Token(Lexeme lexeme, int lineNumber, int columnNumber);
    
    
    Lexeme getLexeme();

	bool hasValidLexeme();

	int getLineNumber();
	int getColumnNumber();

protected:
    
    int _lineNumber;
    int _columnNumber;
    
    Lexeme _lexeme;
};

#endif //TOKEN_H
