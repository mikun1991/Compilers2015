#ifndef SCANNER_H
#define SCANNER_H

#include "Lexeme.h"

#include <string>

using namespace std;
    
class Scanner {
    
public:
    Scanner(string filePath);
    
    Lexeme getNextLexeme();


    
    
private:
    
	string _filePath;
};


#endif //SCANNER_H