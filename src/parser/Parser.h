#ifndef PARSER_H
#define PARSER_H

#include "Grammar.h"
#include "TokenStream.h"

class Parser
{
public:
	Parser(TokenStream* tokens, Grammar *grammar = 0);
	~Parser();

	void parseTokens();
	std::string errMsgs();

protected:
	
	TokenStream* _tokens;
	Grammar* _grammar;
};


#endif //PARSER_H