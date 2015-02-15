#ifndef FINITE_STATE_AUTOMATON
#define FINITE_STATE_AUTOMATON

#include "Token.h"
#include "Resources.h"

#include <istream>

class FiniteStateAutomaton
{

public:

	//static helper functions (regex definitions)

	static bool charIsWhiteSpace(char c);
	static bool charIsDigit(char c);
	static bool charIsUpperAlphabet(char c);
	static bool charIsLowerAlphabet(char c);

	//this can be used to do all the work for the single character FSAs
	static Token singleCharFSA(std::istream* stream, char c, LexemeResources::LexemeType type, int& line, int& currentColumn);


	static Token greaterThan(std::istream* stream, int& line, int& currentColumn);
	static Token equals(std::istream* stream, int& line, int& currentColumn);
	static Token backslash(std::istream* stream, int& line, int& currentColumn);
	static Token period(std::istream* stream, int& line, int& currentColumn);
	static Token endOfFile(std::istream* stream, int& line, int& currentColumn);

	static Token lessThan(std::istream* stream, int& line, int& currentColumn);
	static Token roundLeftBracket(std::istream* stream, int& line, int& currentColumn);
	static Token roundRightBracket(std::istream* stream, int& line, int& currentColumn);
	static Token plus(std::istream* stream, int& line, int& currentColumn);

	static Token colon(std::istream* stream, int& line, int& currentColumn);
	static Token scolon(std::istream* stream, int& line, int& currentColumn);
	static Token comma(std::istream* stream, int& line, int& currentColumn);
	static Token minus(std::istream* stream, int& line, int& currentColumn);
	static Token times(std::istream* stream, int& line, int& currentColumn);

	static Token number(std::istream* stream, int& line, int& currentColumn);
	static Token identifier(std::istream* stream, int& line, int& currentColumn);
	static Token stringLiteral(std::istream* stream, int& line, int& currentColumn);

	static Token comment(std::istream* stream, int& line, int& currentColumn);

	static Token whiteSpace(std::istream* stream, int& line, int& currentColumn);
};

#endif //FINITE_STATE_AUTOMATON