#include "Symbol.h"

using namespace LexemeResources;
using namespace std;


Symbol::Symbol()
	: _dataType(Unknown), _level(-1), _offset(-1), _size(-1)
{
}

Symbol::Symbol(Lexeme lex, LexemeResources::DataType dataType, int level, int offset, int size)
	:_lexeme(lex), _dataType(dataType), _level(level), _offset(offset), _size(size)
{
}

Lexeme Symbol::lexeme() const
{
	return _lexeme;
}

DataType Symbol::dataType() const
{
	return _dataType;
}

int Symbol::level() const
{
	return _level;
}

int Symbol::offset() const
{
	return _offset;
}

int Symbol::size() const
{
	return _size;
}


