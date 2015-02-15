#ifndef TOKEN_H
#define TOKEN_H

#include "Lexeme.h"
#include "Resources.h"


class Token
{

public:

	Token();
	Token(LexemeResources::LexemeType type, std::string name, int lineNumber, int columnNumber);
	Token(Lexeme lexeme, int lineNumber, int columnNumber);

	void setLexeme(Lexeme newLexeme);
	Lexeme getLexeme() const;

	bool hasValidLexeme() const;

	int getLineNumber() const;
	int getColumnNumber() const;

	LexemeResources::LexemeType getType() const;


protected:

	int _lineNumber;
	int _columnNumber;

	Lexeme _lexeme;
};

#endif //TOKEN_H
