#include "Lexeme.h"

const char* TypeAsString[27] = {
	/* Invalid */

	"MP_INVALID",

	/* Identifiers and Literals */

	"MP_IDENTIFIER", //(letter | "_"(letter | digit)){["_"](letter | digit)}
	"MP_INTEGER_LIT", //digit{digit}
	"MP_FIXED_LIT", //digit{digit} "." digit{digit} 
	"MP_FLOAT_LIT", // (digit{digit} | digit{digit} "." digit{digit}) ("e"|"E")["+"|"-"]digit{digit}
	"MP_STRING_LIT", //"'" {"''" | AnyCharacterExceptApostropheOrEOL} "'" 

	/* Symbols */

	"MP_PERIOD", //         "."
	"MP_COMMA", //         ","
	"MP_SCOLON", //         ";"
	"MP_LPAREN", //         "("
	"MP_RPAREN", //        ")"
	"MP_EQUAL",  //        "="
	"MP_FLOAT_DIVIDE", //   "/"
	"MP_GTHAN",  //        ">"
	"MP_GEQUAL", //        ">="
	"MP_LTHAN",  //        "<"
	"MP_LEQUAL", //         "<="
	"MP_NEQUAL", //         "<>"
	"MP_ASSIGN", //        ":="
	"MP_PLUS", //          "+"
	"MP_MINUS", //         "-"
	"MP_TIMES", //         "*"
	"MP_COLON", //		":"

	/* End of File */

	"MP_EOF",

	/* Errors */

	"MP_RUN_COMMENT", // starts with { and end with a }
	"MP_RUN_STRING",
	"MP_ERROR"
};


Lexeme::Lexeme()
	:_type(LexemeType::MP_INVALID), _value("")
{
	

}

Lexeme::Lexeme(LexemeType type, string value)
	:_type(type), _value(value)
{
}

Lexeme::LexemeType Lexeme::getType()
{
	return _type;
}

string Lexeme::getValue()
{
	return _value;
}

string Lexeme::typeToName()
{
	return TypeAsString[(int) _type];
}
