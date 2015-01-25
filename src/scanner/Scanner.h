#ifndef SCANNER_H
#define SCANNER_H

#include "Lexeme.h"


using namespace std{
    
class Scanner {
    
public:
    Scanner(string filePath);
    
    Lexeme getNextLexeme();
    
    
private:
    
    
};


}
#endif //SCANNER_H