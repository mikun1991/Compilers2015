
#ifndef LEXEME_RESOURCES
#define LEXEME_RESOURCES

#include <initializer_list>
#include <string>
#include <list>

/******************************************
**  Keep all of the static data here, such as 
**  the token/lexeme types , the reserved words
**  and lexemetypes as strings
*******************************************/

namespace LexemeResources
{

	static const char* LexemeNames[60] = {
		//--------------------------------
		// Reserved Words
		//--------------------------------
		
		"MP_AND",
		"MP_BEGIN",
		"MP_BOOLEAN",
		"MP_DIV", // /
		"MP_DO",
		"MP_DOWNTO",
		"MP_ELSE",
		"MP_END",
		"MP_FALSE",
		"MP_FIXED",
		"MP_FLOAT",
		"MP_FOR",
		"MP_FUNCTION",
		"MP_IF",
		"MP_INTEGER",
		"MP_MOD", //%
		"MP_NOT",
		"MP_OR",
		"MP_PROCEDURE",
		"MP_PROGRAM",
		"MP_READ",
		"MP_REPEAT",
		"MP_STRING",
		"MP_THEN",
		"MP_TO",
		"MP_TRUE",
		"MP_Type",
		"MP_UNTIL",
		"MP_VAR",
		"MP_WHILE",
		"MP_WRITE",
		"MP_WRITELN",

		//---------------------------------
		// Invalid (for invalid characters)
		//---------------------------------

		"MP_INVALID",

		//---------------------------------
		// Identifiers and Literals 
		//---------------------------------

		"MP_IDENTIFIER",   //(letter | "_"(letter | digit)){["_"](letter | digit)}
		"MP_INTEGER_LIT",  //digit{digit}
		"MP_FIXED_LIT",    //digit{digit} "." digit{digit}
		"MP_FLOAT_LIT",	  //(digit{digit} | digit{digit} "." digit{digit}) ("e"|"E")["+"|"-"]digit{digit}
		"MP_STRING_LIT",  //"'" {"''" | AnyCharacterExceptApostropheOrEOL} "'"

		//---------------------------------
		// Symbols 
		//---------------------------------

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

		//---------------------------------
		// End of File
		//---------------------------------

		"MP_EOF",

		//---------------------------------
		// Errors
		//---------------------------------

		"MP_RUN_COMMENT", // starts with '{' and ends with a '}'
		"MP_RUN_STRING", 
		"MP_ERROR",

		//-------------------------------
		// Others - In reality these never make it out ofthe scanner
		//-------------------------------

		"MP_WHITESPACE" 

	};

	static enum LexemeType{
		//--------------------------------
		// Reserved Words
		//--------------------------------

		MP_AND,
		MP_BEGIN,
		MP_BOOLEAN,
		MP_DIV,
		MP_DO,
		MP_DOWNTO,
		MP_ELSE,
		MP_END,
		MP_FALSE,
		MP_FIXED,
		MP_FLOAT,
		MP_FOR,
		MP_FUNCTION,
		MP_IF,
		MP_INTEGER,
		MP_MOD,
		MP_NOT,
		MP_OR,
		MP_PROCEDURE,
		MP_PROGRAM,
		MP_READ,
		MP_REPEAT,
		MP_STRING,
		MP_THEN,
		MP_TO,
		MP_TRUE,
		MP_Type,
		MP_UNTIL,
		MP_VAR,
		MP_WHILE,
		MP_WRITE,
		MP_WRITELN,

		//---------------------------------
		// Invalid (for invalid characters)
		//---------------------------------

		MP_INVALID,

		//---------------------------------
		// Identifiers and Literals 
		//---------------------------------

		MP_IDENTIFIER, //(letter | "_"(letter | digit)){["_"](letter | digit)}
		MP_INTEGER_LIT, //digit{digit}
		MP_FIXED_LIT, //digit{digit} "." digit{digit} 
		MP_FLOAT_LIT, // (digit{digit} | digit{digit} "." digit{digit}) ("e"|"E")["+"|"-"]digit{digit}
		MP_STRING_LIT, //"'" {"''" | AnyCharacterExceptApostropheOrEOL} "'" 

		//---------------------------------
		// Symbols 
		//---------------------------------

		MP_PERIOD, //         "."
		MP_COMMA, //         ","
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

		//---------------------------------
		// End of File
		//---------------------------------

		MP_EOF,

		//---------------------------------
		// Errors
		//---------------------------------

		MP_RUN_COMMENT, // starts with { and end with a }
		MP_RUN_STRING,
		MP_ERROR,

		//-------------------------------
		// Others - In reality these never make it out ofthe scanner
		//-------------------------------

		MP_WHITESPACE

	};

	//these have to be in alphabetic order for the
	//binary serach to run correctly
	static const char* ReservedWords[32] = {
		"and",					//1
		"begin",
		"boolean",				//3
		"div",
		"do",					//5
		"downto",
		"else",					//7
		"end",
		"false",				//9
		"fixed",
		"float",				//11
		"for", 
		"function",				//13
		"if",
		"integer",				//15
		"mod", 
		"not",					//17
		"or",
		"procedure",			//19
		"program",
		"read",					//21
		"repeat",
		"string",				//23
		"then",
		"to",					//25
		"true",					
		"type",					//27
		"until",
		"var",					//29
		"while",
		"write",				//31
		"writeln" };


	enum DataType
	{
		IntData = 0,
		StringData,
		FloatData,
		BoolData,
		VoidData,

		AddressInt,
		AddressString,
		AddressFloat,
		AddressBool,

		UnknownData		//others ?
	};


	//Some nice helper functions/structs
	static const std::string asStr(LexemeType type)
	{
		return std::string(LexemeNames[type]);
	}

	class TypeList
	{
	public:
		TypeList() { ; }

		std::string asStr()
		{
			std::string listString;
			bool first = true;
			for (LexemeType t : _types){
				if (first){
					first = false;
				}
				else{
					listString += ", ";
				}
				listString += LexemeResources::asStr(t);
			}
			return listString;
		}

		TypeList operator<<(LexemeType type)
		{
			_types.push_back(type);
			return *this;
		}
		//things that could be useful:
		//	contains()
		//  append()
	private:
		std::list<LexemeType> _types;
	};
};

#endif //LEXEME_RESOURCES