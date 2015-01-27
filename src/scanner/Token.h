#ifndef TOKEN_H
#define TOKEN_H

#include "Lexeme.h"

#include <string>

using namespace std;

class Token {
    
    
public:
	enum TokenError{ 
		InvalidLanguageChar,  //character is not supported in this language
		EndOfFile, //End of the file has been reached
		InvalidFile //Invalid file pointer
	};

	Token ();
    Token (string name, Lexeme lexeme, int lineNumber, int columnNumber );
    
    
protected:
    
    int _lineNumber;
    int _columnNumber;
    
    Lexeme _lexeme;
    string _name;
};

#endif //TOKEN_H