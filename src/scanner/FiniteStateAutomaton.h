#ifndef FINITE_STATE_AUTOMATON
#define FINITE_STATE_AUTOMATON

#include "Lexeme.h"
#include <istream>

using namespace std;

class FiniteStateAutomaton {
    
    FiniteStateAutomaton(istream* fileStream);
    
    virtual ~FiniteStateAutomaton(){};
public:

    virtual Lexeme getLexeme() = 0;
    
	istream* _filePointer;
};

#endif //FINITE_STATE_AUTOMATON