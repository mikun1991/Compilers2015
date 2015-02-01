#include "Scanner.h"

#include "scanner/Token.h"
#include "scanner/FiniteStateAutomaton.h"

Scanner::Scanner(string filePath)
{
	_filePointer = new ifstream(filePath);
}

Token Scanner::getNextToken()
{
	//switch here
	Token nextToken;
	int count = 0;

	do{
		nextToken = FiniteStateAutomaton::greaterThan(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;

		nextToken = FiniteStateAutomaton::equals(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;

		nextToken = FiniteStateAutomaton::backslash(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;

		nextToken = FiniteStateAutomaton::period(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;

		nextToken = FiniteStateAutomaton::endOfFile(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;

		nextToken = FiniteStateAutomaton::number(_filePointer, _currentRow, _currentColumn);
		if (nextToken.hasValidLexeme()) break;


	} while (false);


	return nextToken;
}

bool Scanner::moveToNextTockenStart()
{

	return false;
}
