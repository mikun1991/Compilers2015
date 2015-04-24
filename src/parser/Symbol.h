#ifndef SYMBOL_H
#define SYMBOL_H

#include "Resources.h"
#include "Lexeme.h"

class Symbol
{
public:
	Symbol();

	Symbol(Lexeme lex,
		LexemeResources::DataType dataType, 
		int level, 
		int offset = -1, 
		int size = -1, 
		std::list<LexemeResources::DataType> arguments = std::list<LexemeResources::DataType>()
		);

	Lexeme lexeme() const;
	LexemeResources::DataType dataType() const;

	int size() const;
	int level() const;
	int offset() const;
	void setOffset(int offset);

protected:


	Lexeme _lexeme;
	LexemeResources::DataType _dataType;

	int _level;
	int _offset;

	int _size;

	std::list<LexemeResources::DataType> _argumentTypes;
};





#endif //SYMBOL_H