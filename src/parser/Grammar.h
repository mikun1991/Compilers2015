#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Token.h"

#include <string>


class Grammar
{

public:


	std::string getError();

private:
	void match(std::string msg = "");
	void error(std::string errorMsg);

	std::string _errString;

	Token _lookAheadToken;


public:


	static bool factor();
	static bool forStatement(); 
	static bool multiplyingOperator(); 
	static bool actualParameter(); 
	static bool actualParameterTail(); 
	static bool addingOperator(); 
	static bool assignmentStatement(); 
	static bool block(); 
	static bool booleanExpression(); 
	static bool compoundStatement(); 
	static bool controlVariable(); 
	static bool emptyStatement(); 
	static bool expression(); 
	static bool factorTail(); 
	static bool finalValue(); 
	static bool formalParameterSection(); 
	static bool formalParameterSectionTail(); 
	static bool functionDeclaration(); 
	static bool functionHeading(); 
	static bool functionIdentifier(); 
	static bool identifierList(); 
	static bool identifierTail(); 
	static bool ifStatement(); 
	static bool initialValue(); 
	static bool optionalActualParameterList(); 
	static bool optionalElsePart(); 
	static bool optionalFormalParameterList(); 
	static bool optionalRelationalPart(); 
	static bool optionalSign(); 
	static bool ordinalExpression(); 
	static bool procedureAndFunctionDeclarationPart(); 
	static bool procedureDeclaration(); 
	static bool procedureHeading(); 
	static bool procedureIdentifier(); 
	static bool procedureStatement(); 
	static bool program(); 
	static bool programHeading(); 
	static bool programIdentifier(); 
	static bool readParameter(); 
	static bool readParameterTail(); 
	static bool readStatement(); 
	static bool relationalOperator(); 
	static bool repeatStatement(); 
	static bool simpleExpression(); 
	static bool statement(); 
	static bool statementPart(); 
	static bool statementSequence(); 
	static bool statementTail(); 
	static bool stepValue(); 
	static bool systemGoal(); 
	static bool term(); 
	static bool termTail(); 
	static bool type(); 
	static bool valueParameterSection(); 
	static bool variableDeclaration(); 
	static bool variableDeclarationPart(); 
	static bool variableDeclarationTail(); 
	static bool variableIdentifier(); 
	static bool variableParameterSection(); 
	static bool whileStatement(); 
	static bool writeParameter(); 
	static bool writeParameterTail(); 
	static bool writeStatement();

};

#endif