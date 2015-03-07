#include "Parser.h"

#include <string>

using namespace std;

struct ParseException : public std::runtime_error
{
	ParseException(std::string const& message)
		: std::runtime_error(message)
	{
	}
};

Parser::Parser(TokenStream* tokens, Grammar* grammar)
	:_tokens(tokens)
{
	if (!grammar){
		_grammar = new Grammar();
	}
}

Parser::~Parser()
{
	//dont assume ownership of the tokenStream
	delete _grammar;
}

void Parser::parseTokens()
{
	_grammar->setTokenStream(_tokens);
	try{
		_grammar->systemGoal();
	}
	catch (ParseException parseErrors){

	}
}

string Parser::errMsgs()
{
	return _grammar->getError();
}

void Parser::printLog()
{
	_grammar->printLog();
}