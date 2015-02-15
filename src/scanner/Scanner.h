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
	Token getNextToken(); 

private:
	Token scanNextToken(); //<- this is the dispatcher 

	//Check to see if the scanned token is a reserved word 
	void checkReserved(Token& token);
	bool moveToNextTokenStart();

	//return -1 if it is not present
	const int indexInReservedWords(const std::string&  name);
	const int indexInReservedWordsHelper(const std::string& name, int top, int middle, int bottom);

	int _currentColumn;
	int _currentRow;

	ifstream* _filePointer;
};


#endif //SCANNER_H
