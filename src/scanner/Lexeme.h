#ifndef LEXEME_H
#define LEXEME_H

#include "Resources.h"

#include <string>

class Lexeme
{

public:
	Lexeme();
	Lexeme(LexemeResources::LexemeType type, std::string value);


	LexemeResources::LexemeType getType() const;
	std::string typeToName() const;
	std::string getValue() const;

protected:

	LexemeResources::LexemeType _type;
	std::string _value;

};

#endif //LEXEME_H
