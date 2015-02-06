#include "TestScanner.h"

#include "Token.h"
#include "FiniteStateAutomaton.h"
#include "Lexeme.h"

#include <sstream>

#include <assert.h>
int main(int argc, char * argv[])
{

	TestScanner::testNumber();
	TestScanner::testIdentifier();
}


bool TestScanner::testNumber()
{
	//TestCase 1
	{
		std::stringstream ss;

		ss << "029311 ";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::number(&ss, line, col);
		//assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_INTEGER_LIT);
	}

	//TestCase 1
	{
		std::stringstream ss;

		ss << "3E4";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::number(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_INTEGER_LIT);
	}

	return true;
}

bool TestScanner::testIdentifier()
{   //isentifier has a form of: (letter | "_"(letter | digit)){["_"](letter | digit)}
	//TestCase 1 - only letters
	{
		std::stringstream ss;

		ss << "dsdad";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 2 - "_" and letters
	{
	std::stringstream ss;

	ss << "_dfszdf";

	int line = 0;
	int col = 0;
	Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
	assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
    }

	//TestCase 3 - "_" and digits
	{
		std::stringstream ss;

		ss << "_345";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 4 - "_" and digits and letters
	{
		std::stringstream ss;

		ss << "_zjdfakj_24b_zf";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 5 - "_" as a last character
	{
		std::stringstream ss;

		ss << "_df9hj_s5zdf_";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 6 - more that one "_" in a row
	{
		std::stringstream ss;

		ss << "_dfsz_h0___df";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 7 - 'unwanted' symbol like @ 
	{
		std::stringstream ss;

		ss << "_@dfszdf";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 8 - only digits
	{
		std::stringstream ss;

		ss << "123";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 9
	{
		std::stringstream ss;

		ss << "_dfszdf";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 10 - start wih digit
	{
		std::stringstream ss;

		ss << "8_dfszdf";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}
	return true;
}