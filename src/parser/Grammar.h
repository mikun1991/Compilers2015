#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Token.h"
#include "TokenStream.h"
#include "Resources.h"

#include <string>
#include <list>
#include <iostream>

class Grammar
{

public:

	std::string getError();

	void setTokenStream(TokenStream* tokens);

	void printLog();

private:
	bool match();
	void logRule(int rule);

	//dont need to pass any other info as we can get it from the 
	//current token, just give what the expected token should have been
	void error(std::string expectedTokenNames);
	void error(LexemeResources::TypeList espectedTypes);

	std::list<std::string> _errStrings;

	//the list of current tokens
	TokenStream* _currentTokens;

	//Syntactic Sugar... mmmhhhmm
	LexemeResources::LexemeType nextTokenType() const;

	//a list of production rules logged while parsing
	std::list<int> _ruleLog;

public:
	 
	 //travis
	 bool factor();
	 bool forStatement(); 
	 bool multiplyingOperator(); 
	 bool actualParameter(); 
	 bool actualParameterTail(); 
	 bool addingOperator(); 
	 bool assignmentStatement(); //<-
	 bool block(); 
	 bool booleanExpression(); 
	 bool compoundStatement(); 
	 bool controlVariable(); //<- 
	 bool emptyStatement(); 
	 bool expression(); 
	 bool factorTail(); 
	 bool finalValue(); 
	 bool formalParameterSection();
     //joe
	 bool formalParameterSectionTail(); 
	 bool functionDeclaration(); 
	 bool functionHeading(); 
	 bool functionIdentifier(); 
	 bool identifierList(); 
	 bool identifierTail(); 
	 bool ifStatement();
	 bool initialValue(); 
	 bool optionalActualParameterList(); 
	 bool optionalElsePart(); 
	 bool optionalFormalParameterList(); 
	 bool optionalRelationalPart(); 
	 bool optionalSign(); 
	 bool ordinalExpression(); 
	 bool procedureAndFunctionDeclarationPart(); 
	 bool procedureDeclaration();
     //aidan
	 bool procedureHeading(); 
	 bool procedureIdentifier(); 
	 bool procedureStatement(); 
	 bool program(); 
	 bool programHeading(); 
	 bool programIdentifier(); 
	 bool readParameter(); 
	 bool readParameterTail(); 
	 bool readStatement(); 
	 bool relationalOperator(); 
	 bool repeatStatement();
	 bool simpleExpression(); 
	 bool statement(); 
	 bool statementPart(); 
	 bool statementSequence(); 
	 bool statementTail();
     //agata
	 bool stepValue(); 
	 bool systemGoal(); 
	 bool term(); 
	 bool termTail(); 
	 bool type(); 
	 bool valueParameterSection(); 
	 bool variableDeclaration(); 
	 bool variableDeclarationPart(); 
	 bool variableDeclarationTail(); 
	 bool variableIdentifier(); 
	 bool variableParameterSection(); 
	 bool whileStatement(); 
	 bool writeParameter(); 
	 bool writeParameterTail(); 
	 bool writeStatement();

};

#endif