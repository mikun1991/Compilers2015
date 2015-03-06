#include "Parser.h"

#include <string>

using namespace std;

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
	_grammar->systemGoal();
}

string Parser::errMsgs()
{
	return _grammar->getError();
}