#ifndef FINITE_STATE_AUTOMATON
#define FINITE_STATE_AUTOMATON

#include "Token.h"
#include <istream>

using namespace std;

class FiniteStateAutomaton {
    
    FiniteStateAutomaton(istream* fileStream);
    
    virtual ~FiniteStateAutomaton(){};
public:

    virtual Token getToken() = 0;

	//static helper functions (regex definitions)
	static bool charIsWhiteSpace(char c);
	static bool charIsDigit(char c);
	static bool charIsUpperAlphabet(char c);
	static bool charIsLowerAlphabet(char c);
    
	istream* _filePointer;
};

#endif //FINITE_STATE_AUTOMATON