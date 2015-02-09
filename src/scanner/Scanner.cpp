#include "Scanner.h"

#include "Token.h"
#include "FiniteStateAutomaton.h"

#include <string>
#include <algorithm>


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

Token Scanner::getNextToken()
{
	Token next = scanNextToken();
	checkReserved(next);
	return next;
}

void Scanner::checkReserved(Token& token)
{
	std::string lowerName = token.getLexeme().getValue();
	std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

	int index = indexInReservedWords(lowerName);
	if (index < 0){
		return;
	}

	//otherwise this is a reserved word and we should update the token accordingly
	Lexeme newLexeme((Lexeme::LexemeType) index, ReservedWords[index]);
	token.setLexeme(newLexeme);
}

int Scanner::indexInReservedWords(const std::string& name)
{
	return indexInReservedWordsHelper(name, 16, 32, 0);
}

int Scanner::indexInReservedWordsHelper(const std::string& name , int location, int upperBound, int lowerBound)
{
	if (location >= upperBound){
		return -1;
	}
	if (location <= lowerBound){
		return -1;
	}
	if (name == ReservedWords[location]){
		return location;
	}
	
	if (name < ReservedWords[location]){
		upperBound = location;
		location -= ((upperBound-1 - lowerBound) / 2);
	}
	else{
		//name > reservedWords[location]
		lowerBound = location;
		location += ((upperBound+1 - lowerBound) / 2);
	}

	return indexInReservedWordsHelper(name, location, upperBound, lowerBound);
}

bool Scanner::moveToNextTokenStart()
{

	return false;
}
