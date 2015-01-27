#ifndef SCANNER_H
#define SCANNER_H

#include "Lexeme.h"

#include <string>
#include <fstream>


using namespace std;
    
class Scanner {
    
public:
    Scanner(string filePath);
    
    Lexeme getNextLexeme();

private:


	bool moveToNextTockenStart();

	int _lastTockenEnd;
	int _beginingOfNextTocken; 


	ifstream* _filePointer;
    
	string _filePath;
};


#endif //SCANNER_H