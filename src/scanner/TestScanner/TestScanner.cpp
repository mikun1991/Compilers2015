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

	return true;
}

bool TestScanner::testIdentifier()
{
	//TestCase 1
	{
		std::stringstream ss;

		ss << "d";

		int line = 0;
		int col = 0;
		Token ret = FiniteStateAutomaton::identifier(&ss, line, col);
		assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_IDENTIFIER);
	}

	//TestCase 2
	{
	std::stringstream ss;

	ss << "_dfszdf";

	int line = 0;
	int col = 0;
	Token ret = FiniteStateAutomaton::number(&ss, line, col);
	assert(ret.getLexeme().getType() == Lexeme::LexemeType::MP_INTEGER_LIT);
}


	return true;
}