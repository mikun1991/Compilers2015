#ifndef LEXEME_H
#define LEXEME_H

#include <string>

using namespace std;

class Lexeme {
    
public:
	//add more types as we go here 

	enum LexemeType{ 
		/* Invalid */

		 MP_INVALID ,

		/* Identifiers and Literals */

		MP_IDENTIFIER , //(letter | "_"(letter | digit)){["_"](letter | digit)}
		MP_INTEGER_LIT , //digit{digit}
		MP_FIXED_LIT , //digit{digit} "." digit{digit} 
		MP_FLOAT_LIT , // (digit{digit} | digit{digit} "." digit{digit}) ("e"|"E")["+"|"-"]digit{digit}
		MP_STRING_LIT , //"'" {"''" | AnyCharacterExceptApostropheOrEOL} "'" 

		/* Symbols */

		MP_PERIOD, //         "."
		MP_COMMA , //         ","
		MP_SCOLON, //         ";"
		MP_LPAREN, //         "("
		MP_RPAREN, //        ")"
		MP_EQUAL,  //        "="
		MP_FLOAT_DIVIDE, //   "/"
		MP_GTHAN,  //        ">"
		MP_GEQUAL, //        ">="
		MP_LTHAN,  //        "<"
		MP_LEQUAL, //         "<="
		MP_NEQUAL, //         "<>"
		MP_ASSIGN, //        ":="
		MP_PLUS, //          "+"
		MP_MINUS, //         "-"
		MP_TIMES, //         "*"
		MP_COLON, //		":"

		/* End of File */

		MP_EOF,

		/* Errors */

		MP_RUN_COMMENT, // starts with { and end with a }
		MP_RUN_STRING,
		MP_ERROR,

	};
    

	string typeToName();

	Lexeme();
	Lexeme(LexemeType type, string value);

	LexemeType getType();
	string getValue();

protected:

	LexemeType _type;
	string _value;

};

#endif //LEXEME_H
