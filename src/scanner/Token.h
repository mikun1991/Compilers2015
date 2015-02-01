#ifndef TOKEN_H
#define TOKEN_H

#include "Lexeme.h"

#include <string>

using namespace std;

class Token {
    
    
public:

	Token ();
    Token (Lexeme lexeme, int lineNumber, int columnNumber );
    
    
    Lexeme getLexeme();


protected:
    
    int _lineNumber;
    int _columnNumber;
    
    Lexeme _lexeme;
};

#endif //TOKEN_H
