#ifndef LEXEME_H
#define LEXEME_H

#include <string>

using namespace std;

class Lexeme {
    
public:
	//add more types as we go here 
	enum Type{ Invalid,
		GreaterThan,
		GreaterThanOrEqual
	};
    
	Lexeme();
	Lexeme(Type type, string value);

	Type getType();
	string getValue();

protected:

	Type _type;
	string _value;

};

#endif //LEXEME_H