#ifndef TOKEN_STREAM
#define TOKEN_STREAM

#include "Token.h"
#include "Resources.h"

#include <queue>

class TokenStream
{
public:

	bool moveAhead();
	
	
	bool nextToken(Token& nextToken) const;
	LexemeResources::LexemeType nextTokenType() const;
	
	void addToken(Token newToken);

protected:

	std::queue<Token> _toRead;
};


#endif // TOKEN_STREAM