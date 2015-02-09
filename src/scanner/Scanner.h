#ifndef SCANNER_H
#define SCANNER_H

#include "Lexeme.h"
#include "Token.h"

#include <string>
#include <fstream>


using namespace std;
    
class Scanner {
    
public:
    Scanner(string filePath);

    Token getNextToken(); //<- this is the dispatcher 

	bool hasError();
	string getError();

private:

	Token scanNextToken();

	void checkReserved(Token& token);

	bool moveToNextTokenStart();

	//return -1 if it is not present
	int indexInReservedWords(const std::string&  name);
	int indexInReservedWordsHelper(const std::string&, int locaiton, int upperBound, int lowerBound);

	int _currentColumn;
	int _currentRow;

	bool _hasError;
	string _errorString;

	ifstream* _filePointer;
	string _filePath;
};


#endif //SCANNER_H
