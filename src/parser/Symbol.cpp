#include "Symbol.h"

using namespace LexemeResources;
using namespace std;


Symbol::Symbol()
	: _dataType(UnknownData), _level(-1), _offset(-1), _size(-1), _isFunProd(false)
{
}

Symbol::Symbol(Lexeme lex, LexemeResources::DataType dataType, int level, int offset, int size, list<DataType> arguments)
	: _lexeme(lex), _dataType(dataType), _level(level), _offset(offset), _size(size), _argumentTypes(arguments), _isFunProd(false)
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

void Symbol::setOffset(int offset)
{
	_offset = offset;
}

list<DataType> Symbol::argumentTypes() const
{
	return _argumentTypes;
}

int Symbol::label() const
{
	return _label;
}

void Symbol::setLabel(int label)
{
	_label = label;
}

void Symbol::setArgumentTypes(list<DataType> newArguments)
{ 
	_argumentTypes = newArguments;
}

void Symbol::setFunProd(bool isFunProd)
{
	_isFunProd = isFunProd;
}

bool Symbol::funProd()
{
	return _isFunProd;
}