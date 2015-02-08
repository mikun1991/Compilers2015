#include "Scanner.h"

#include "Token.h"
#include "FiniteStateAutomaton.h"



//// RESERVED WORDS ///////
const char* ReservedWords[32] = {
		"and",
		"begin",
		"Boolean",
		"div",
		"do",
		"downto",
		"else",
		"end",
		"false",
		"fixed",
		"float",
		"for",
		"function",
		"if",
		"integer",
		"mod",
		"not",
		"or",
		"procedure",
		"program",
		"read",
		"repeat",
		"string",
		"then",
		"true",
		"to",
		"type",
		"until",
		"var",
		"while",
		"write",
		"writeln"};



Scanner::Scanner(string filePath)
{
	_filePointer = new ifstream(filePath);
	_currentRow = 0;
	_currentColumn = 0;
}

Token Scanner::getNextToken()
{
	Token next = scanNextToken();

	std::string name = next.getLexeme().getValue();

	//if(ReservedWords.contains(name)){
	//	int index = ReservedWords.indexOf(name);
	//}

	return next;
}


Token Scanner::scanNextToken()
{
	//switch here
	Token nextToken;
	int count = 0;

	nextToken = FiniteStateAutomaton::greaterThan(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::equals(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::backslash(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::period(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::endOfFile(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::lessThan(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::roundLeftBracket(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::roundRightBracket(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::plus(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::colon(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::comma(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::minus(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::times(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::number(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::identifier(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::stringLiteral(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::comment(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	nextToken = FiniteStateAutomaton::whiteSpace(_filePointer, _currentRow, _currentColumn);
	if (nextToken.hasValidLexeme()) return nextToken;

	std::string name;
	name += _filePointer->get();
	return Token(Lexeme::MP_INVALID, name, _currentRow, _currentColumn);
	_currentColumn++;
}

bool Scanner::moveToNextTokenStart()
{

	return false;
}
