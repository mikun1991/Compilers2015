#ifndef TOKEN_H
#define TOKEN_H

#include "Lexeme.h"

using namespace std;

class Token {
    
    
public:
    Token (string name, Lexeme lexeme, int lineNumber, int columnNumber );
    
    
protected:
    
    int _lineNumber;
    int _columnNumber;
    
    Lexeme _lexeme;
    string _name;
};

#endif //TOKEN_H