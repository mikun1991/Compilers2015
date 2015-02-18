#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Token.h"

#include "Scanner.h"

#include <string>


class Grammar
{

public:


	std::string getError();

private:
	bool match(LexemeResources::LexemeType type);
	void error(int errorLine, int errorColumn);

	std::string _errString;

	Token _lookAheadToken;

	Scanner _currentScanner;


public:


	 bool factor();
	 bool forStatement(); 
	 bool multiplyingOperator(); 
	 bool actualParameter(); 
	 bool actualParameterTail(); 
	 bool addingOperator(); 
	 bool assignmentStatement(); 
	 bool block(); 
	 bool booleanExpression(); 
	 bool compoundStatement(); 
	 bool controlVariable(); 
	 bool emptyStatement(); 
	 bool expression(); 
	 bool factorTail(); 
	 bool finalValue(); 
	 bool formalParameterSection(); 
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
	 //last 20, Joe
	 bool simpleExpression(); 
	 bool statement(); 
	 bool statementPart(); 
	 bool statementSequence(); 
	 bool statementTail(); 
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