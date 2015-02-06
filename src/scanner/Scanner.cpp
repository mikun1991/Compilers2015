#include "Scanner.h"

#include "scanner/Token.h"
#include "scanner/FiniteStateAutomaton.h"

Scanner::Scanner(string filePath)
{
	_filePointer = new ifstream(filePath);
	_currentRow = 0;
	_currentColumn = 0;
}

Token Scanner::getNextToken()
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
	return Token(Lexeme::LexemeType::MP_INVALID, name, _currentRow, _currentColumn);
	_currentColumn++;
}

bool Scanner::moveToNextTokenStart()
{

	return false;
}
