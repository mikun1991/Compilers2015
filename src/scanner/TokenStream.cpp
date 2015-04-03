#include "TokenStream.h"

using namespace LexemeResources;

bool TokenStream::moveAhead()
{
	if (_toRead.empty())
		return false;
	_toRead.pop();
	return true;
}

bool TokenStream::nextToken(Token& next) const
{
	if (_toRead.empty())
		return false;

	next = _toRead.front();
	return true;
}

LexemeType TokenStream::nextTokenType() const
{
	if (_toRead.empty())
		return MP_ERROR;
	return _toRead.front().getType();
}

Lexeme TokenStream::currentLexeme()
{
	if (_toRead.empty())
	{
		return Lexeme();
	}
	return _toRead.front().getLexeme();
}

void TokenStream::addToken(Token newToken)
{
	_toRead.push(newToken);
}