#ifndef FINITE_STATE_AUTOMATON
#define FINITE_STATE_AUTOMATON


#include "Lexeme.h"

using namespace std;

class FiniteStateAutomaton {
    
    FiniteStateAutomaton();
    
    virtual ~FiniteStateAutomaton(){};
public:
    
    virtual getLexeme() = 0;
    

    
};

#endif //FINITE_STATE_AUTOMATON