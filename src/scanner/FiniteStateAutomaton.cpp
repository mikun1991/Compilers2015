#include "FiniteStateAutomaton.h"
#include "Token.h"
#include "Lexeme.h"

#include <iostream>

bool FiniteStateAutomaton::charIsWhiteSpace(char c)
{
	if (c == ' ') return true;
	if (c == '\t') return true;
	if (c == '\n') return true;

	return false;
}

bool FiniteStateAutomaton::charIsDigit(char c)
{
	//48 -57
	if ((int)c > 47 && (int)c < 58)
		return true;
	
	return false;
}

bool FiniteStateAutomaton::charIsUpperAlphabet(char c)
{
	if ((int) c > 64 && (int)c < 91)
		return true;
	return false;
}

bool FiniteStateAutomaton::charIsLowerAlphabet(char c)
{
	//97 - 122
	if (c > 96 && c < 123)
		return true;

	return false;
}

Token FiniteStateAutomaton::singleCharFSA(istream* stream, char c, Lexeme::LexemeType type, int& line, int& currentColumn)
{
	char next;
	string name;
	//Start State
	{
		next = stream->peek();
		if (next == c){ //transition
			name += stream->get();
			currentColumn++;
			goto Accept;
		}
		goto Reject;
	}
Accept:
	{
		return Token(type, name, line, currentColumn);
	}
Reject:
	{
		return Token();
	}
}

Token FiniteStateAutomaton::greaterThan(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;
//Start State
	{
		//look without taking
		next = stream->peek();
		if (next == '>'){ //transition
			//move ahead next char
			name += stream->get(); //we already know it is a '>'
			currentColumn++;
			goto GreaterThan;
		}
		//default condition
		goto Reject;
	}

GreaterThan:
	{
		next = stream->peek();
		if (next == '='){ //transition
			//take the '='
			name += stream->get();
			currentColumn++;
			goto GreaterThanOrEqual;
		}
		//accept greater than
		return Token(Lexeme::MP_GTHAN, name, line, currentColumn);
	}

GreaterThanOrEqual:
	{
		//can go no further
		return Token(Lexeme::MP_GEQUAL, name, line, currentColumn);
	}

Reject:
	{
		//nothing here, return default init token (invalid)
		return Token();
	}
}


Token FiniteStateAutomaton::lessThan(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;
	//Start State
	{
		//look without taking
		next = stream->peek();
		if (next == '<'){ //transition
			//move ahead next char
			name += stream->get(); //we already know it is a '<'
			currentColumn++;
			goto LessThan;
		}
		//default condition
		goto Reject;
	}

LessThan:
	{
		next = stream->peek();
		if (next == '='){ //transition
			//take the '='
			name += stream->get();
			currentColumn++;
			goto LessThanOrEqual;


		}

		if (next == '>'){//transition
			//take the '>'
			name += stream->get();
			currentColumn++;
			goto Negation;

		}
		//accept less than
		return Token(Lexeme::MP_LTHAN, name, line, currentColumn);
	}

LessThanOrEqual:
	{
		//can go no further
		return Token(Lexeme::MP_LEQUAL, name, line, currentColumn);
	}

Negation:
	{
		//accept negation
		return Token(Lexeme::MP_NEQUAL, name, line, currentColumn);
	}
Reject:
	{
		//nothing here, return default init token (invalid)
		return Token();
	}
}

Token FiniteStateAutomaton::colon(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;

//Start State
	{
		//look without taking
		next = stream->peek();
		if (next == ':'){//transition
			//move ahead next character
			name += stream->get();
			currentColumn++;
			goto Colon;
		}
		//default
		goto Reject;
	}

Colon:
	{
		next = stream->peek();
		if (next == '='){
			name += stream->get();
			currentColumn++;
			goto Assign;
		}
		//accept colon
		return Token(Lexeme::MP_COLON, name, line, currentColumn);
	}

Assign:
	{
		//accept assign
		return Token(Lexeme::MP_ASSIGN, name, line, currentColumn);
	}

Reject:
	{
		return Token();
	}
}

Token FiniteStateAutomaton::equals(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '=', Lexeme::MP_EQUAL, line, currentColumn);
}

Token FiniteStateAutomaton::backslash(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '/', Lexeme::MP_FLOAT_DIVIDE, line, currentColumn);
}

Token FiniteStateAutomaton::period(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '.', Lexeme::MP_PERIOD, line, currentColumn);
}

Token FiniteStateAutomaton::plus(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '+', Lexeme::MP_PLUS, line, currentColumn);
}

Token FiniteStateAutomaton::roundLeftBracket(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '(', Lexeme::MP_LPAREN, line, currentColumn);
}

Token FiniteStateAutomaton::roundRightBracket(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, ')', Lexeme::MP_RPAREN, line, currentColumn);
}

Token FiniteStateAutomaton::scolon(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, ';', Lexeme::MP_SCOLON, line, currentColumn);
}

Token FiniteStateAutomaton::comma(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, ',', Lexeme::MP_COMMA, line, currentColumn);
}

Token FiniteStateAutomaton::minus(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '-', Lexeme::MP_MINUS, line, currentColumn);
}

Token FiniteStateAutomaton::times(istream* stream, int& line, int& currentColumn)
{
	return singleCharFSA(stream, '*', Lexeme::MP_TIMES, line, currentColumn);
}


Token FiniteStateAutomaton::endOfFile(istream* stream, int& line, int& currentColumn)
{
	int pos = stream->tellg();
	char next = stream->get();
	string name;
	if (next == EOF|| next < 0){//then this is the end of the file
		return Token(Lexeme::MP_EOF, name , line, currentColumn);
	}
	stream->seekg(pos);
	return Token();
}


Token FiniteStateAutomaton::identifier(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;

	Lexeme::LexemeType lastGoodType = Lexeme::MP_INVALID;
	int lastGoodPosition = stream->tellg();
	string temp;

//start state	
	next = stream->peek();

	if (charIsUpperAlphabet(next) || charIsLowerAlphabet(next))
	{
		name += stream->get();
		currentColumn++;
		goto Identifier;
	}

	if (next == '_'){
		lastGoodPosition = stream->tellg();
		temp += stream->get();
		goto Underscore;
	}

	goto Reject;

Identifier:
	{
		next = stream->peek();

		if (charIsDigit(next) || charIsUpperAlphabet(next) || charIsLowerAlphabet(next))
		{
			name += stream->get();
			currentColumn++;
			goto Identifier;
		}

		if (next == '_'){
			lastGoodPosition = stream->tellg();
			temp += stream->get();
			goto Underscore;
		}
		
		
		lastGoodType = Lexeme::MP_IDENTIFIER;
		return Token(lastGoodType, name, line, currentColumn);
		//goto Reject; //???????????????
	
	}

Underscore:
	{
		next = stream->peek();

		if (charIsDigit(next) || charIsUpperAlphabet(next) || charIsLowerAlphabet(next))
		{
			name += stream->get();
			currentColumn++;
			goto Identifier;
		}

		stream->seekg(lastGoodPosition);
		return Token(lastGoodType, name, line, currentColumn);
	}

Reject:
	{
		if (lastGoodType == Lexeme::MP_INVALID){
			return Token();
		}
		stream->seekg(lastGoodPosition);
		return Token(lastGoodType, name, line, currentColumn);
	}
}

Token FiniteStateAutomaton::number(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;

	Lexeme::LexemeType lastGoodType = Lexeme::MP_INVALID;
	int lastGoodPosition = stream->tellg();
	string temp;

	//start state
	{
		next = stream->peek();
		if (charIsDigit(next)){
			name += stream->get();
			currentColumn++;
			goto IntegerLit;
		}
		goto Reject;
	}

IntegerLit://digit{digit}
	{
		next = stream->peek();

		lastGoodType = Lexeme::MP_INTEGER_LIT;

		if (charIsDigit(next)){
			name += stream->get();
			currentColumn++;
			goto IntegerLit;
		}

		if (next == '.'){
			lastGoodPosition = stream->tellg();
			temp += stream->get();
			goto FixedLit;
		}

		if (next == 'e' || next == 'E'){
			lastGoodPosition = stream->tellg();
			temp += stream->get();
			goto FloatLitE;
		}

		return Token(lastGoodType, name, line, currentColumn);
	}

FixedLit: //got here from a "." 
	{
		next = stream->peek();

		if (charIsDigit(next)){
			temp += stream->get();
			goto FixedLitTrailingInt;
		}
		
		goto Reject;
	}

FixedLitTrailingInt:
	{
		next = stream->peek();

		if (next == 'e' || next == 'E'){
			//fixedlit is done 
			name += temp;
			currentColumn += temp.size();
			lastGoodType = Lexeme::MP_FIXED_LIT;
			temp.clear();

			//go for the float lit
			lastGoodPosition = stream->tellg();
			temp += stream->get(); //get the 'e'
			goto FloatLitE;
		}

		name += temp;
		currentColumn += temp.size();

		return Token(Lexeme::MP_FIXED_LIT, name, line, currentColumn);
	}

FloatLitE:
	{
		next = stream->peek();
		
		if (next == '+' || next == '-'){
			temp += stream->get();
			goto FloatLitPlusMinus;
		}

		goto Reject;
	}

FloatLitPlusMinus:
	{
		next = stream->peek();

		if (charIsDigit(next)){
			temp += stream->get();
			goto FloatLitTrailingInt;
		}

		goto Reject;
	}

FloatLitTrailingInt:
	{
		next = stream->peek();

		if (charIsDigit(next)){
			temp += stream->get();
			goto FloatLitTrailingInt;
		}

		name += temp;
		currentColumn += temp.size();
		return Token(Lexeme::MP_FLOAT_LIT, name, line, currentColumn);
	}

Reject:
	{
		if (lastGoodType == Lexeme::MP_INVALID){
			return Token();
		}
		stream->seekg(lastGoodPosition);
		return Token(lastGoodType, name, line, currentColumn);	
	}

}

Token FiniteStateAutomaton::stringLiteral(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;
	int startColumn = currentColumn;

	Lexeme::LexemeType lastGoodType = Lexeme::MP_INVALID;
	//int lastGoodPosition = stream->tellg();

//start state
	{
		next = stream->peek();
		if (next == '\''){
			stream->ignore(1);
			currentColumn++;
			goto OddApostrophes;
		}
		//if you don't see an apostrophe
		goto Reject;
	}

OddApostrophes:  //this is a non-accept state looking for more characters in the string literal
	{
		next = stream->peek();
		if (next == '\''){
			//if you see another apostrophe need to check for end of string or escaped apostrophe character
			lastGoodType = Lexeme::MP_STRING_LIT;
			stream->ignore(1);
			currentColumn++;
			goto EvenApostrophes;
		}
		
		if (next == '\n'){
			//if you encounter EOL in open string you return MP_RUN_STRING error 
			lastGoodType = Lexeme::MP_RUN_STRING;
			goto Reject;
		}

		if (next == EOF){
			//if you encounter EOF in open string you return MP_RUN_STRING error
			lastGoodType = Lexeme::MP_RUN_STRING;
			goto Reject;
		}

		//otherwise add character to the string literal and keep looking
		name += stream->get();
		currentColumn++;
		goto OddApostrophes;
	}

EvenApostrophes:  //this is a state that checks for more apostrophes, otherwise accepts and returns string literal 
	{
		next = stream->peek();
		if (next == '\''){
			//if you see another apostrophe, it is an escaped apostrophe and is added to the string
			name += stream->get();
			currentColumn++;
			goto OddApostrophes;
		}

		//otherwise you have a valid string literal
		return Token(Lexeme::MP_STRING_LIT, name, line, startColumn);
	}

Reject:  //returns a blank token if this method was called in error, otherwise returns MP_RUN_STRING errors
	{
		if (lastGoodType == Lexeme::MP_INVALID){
			return Token();
		}
		return Token(lastGoodType, name, line, startColumn);
	}
	
}

Token FiniteStateAutomaton::comment(istream* stream, int& line, int& currentColumn)
{
	char next;
	Lexeme lex = Lexeme();
	int startColumn = currentColumn;
	int startLine = line;

//start state
	{
		next = stream->peek();
		if (next == '{'){
			stream->ignore(1);
			currentColumn++;
			goto IgnoreComments;
		}
		//if you don't see a {
		goto Reject;

	}

IgnoreComments:  //state that ignores comments while updating line and currentColumn, and watches for MP_RUN_COMMENT error
	{
		next = stream->peek();
		
		//if you encounter a newline inside a comment, reset currentColumn, increment line, and continue processing comment
		if (next == '\n'){
			stream->ignore(1);
			currentColumn = 0;
			line++;
			goto IgnoreComments;
		}

		//if you encounter EOF inside a comment, return MP_RUN_COMMENT error
		if (next == EOF){
			return Token(Lexeme::MP_RUN_COMMENT, " ", startLine, startColumn);
		}

		//if you encounter }, this indicates end of comments
		if (next == '}'){
			stream->ignore(1);
			currentColumn++;
			return Token(lex, startLine, startColumn);
		}

		//if you encounter another {, alert programmer of possible error with unclosed comment
		if (next == '{'){
			stream->ignore(1);
			currentColumn++;
			goto IgnoreComments;
		}

		//otherwise continue processing comment
		stream->ignore(1);
		currentColumn++;
		goto IgnoreComments;
	}

Reject:
	{
		return Token();
	}
}

Token FiniteStateAutomaton::whiteSpace(istream* stream, int& line, int& currentColumn)
{
	char next;
	string name;
	//Start State
	{
		next = stream->peek();

		if (next == '\n'){
			name += stream->get();
			currentColumn = 0;
			line++;
			goto Accept;
		}
		if (charIsWhiteSpace(next)){ //transition
			name += stream->get();
			currentColumn++;
			goto Accept;
		}
		goto Reject;
	}
Accept:
	{
		return Token(Lexeme::MP_WHITESPACE, name, line, currentColumn);
	}
Reject:
	{
		return Token();
	}
}
