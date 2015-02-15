#ifndef SCANNER_H
#define SCANNER_H

#include "Lexeme.h"
#include "Token.h"

#include <string>
#include <fstream>


using namespace std;

class Scanner
{

public:
	Scanner(string filePath);
	~Scanner();

	bool isValid();

	Token getNextToken(); //<- this is the dispatcher 

private:
	Token scanNextToken();
	void checkReserved(Token& token);
	bool moveToNextTokenStart();

	//return -1 if it is not present
	const int indexInReservedWords(const std::string&  name);
	const int indexInReservedWordsHelper(const std::string&, int locaiton, int upperBound, int lowerBound) ;

	int _currentColumn;
	int _currentRow;

	ifstream* _filePointer;
};


#endif //SCANNER_H
