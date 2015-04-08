#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Token.h"
#include "TokenStream.h"
#include "Resources.h"
#include "SemanticRecord.h"
#include "SemanticAnalyzer.h"
#include "SemanticRecord.h"
#include "Lexeme.h"

#include <string>
#include <list>
#include <iostream>

class Grammar
{

public:

	std::string getError();

	void setTokenStream(TokenStream* tokens);

	void printLog();
	SemanticAnalyser* _semanticAnalyser;

private:
	//TODO: need to decide if we will use this
	//SemanticOrganizer* _semanticOrganizer;


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
	Token  nextToken() const;

	//a list of production rules logged while parsing
	std::list<int> _ruleLog;

	//access to the current Token's lexeme for semantic records
	Lexeme currentLexeme();

public:
	 
	 bool factor(SemanticRecord&);
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
	 bool factorTail(SemanticRecord&); 
	 bool finalValue(); 
	 bool formalParameterSection(SemanticRecord&);
	 bool formalParameterSectionTail(SemanticRecord&); 
	 bool functionDeclaration();  // close function SymbolTable  
	 bool functionHeading();   // create function SymbolTable, add function parameters symbols
	 bool functionIdentifier(SemanticRecord&); 
	 bool identifierList(SemanticRecord&); 
	 bool identifierTail(SemanticRecord&); 
	 bool ifStatement();
	 bool initialValue();  
	 bool optionalActualParameterList();  
	 bool optionalElsePart(); 
	 bool optionalFormalParameterList(SemanticRecord&); 
	 bool optionalRelationalPart(); 
	 bool optionalSign(); 
	 bool ordinalExpression(); 
	 bool procedureAndFunctionDeclarationPart(); 
	 bool procedureDeclaration();  //Close procedure SymbolTable
	 bool procedureHeading();   //Create procedure SymbolTable
	 bool procedureIdentifier(SemanticRecord&); 
	 bool procedureStatement(); 
	 bool program();  //Close program SymbolTable 
	 bool programHeading();  //Create program SymbolTable
	 bool programIdentifier(SemanticRecord&); 
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
	 bool stepValue(); 
	 bool systemGoal(); 
	 bool term(SemanticRecord&); 
	 bool termTail(); 
	 bool type(SemanticRecord&); 
	 bool valueParameterSection(SemanticRecord&); 
	 bool variableDeclaration();   // add symbols to current symbol tables
	 bool variableDeclarationPart(); 
	 bool variableDeclarationTail(); 
	 bool variableIdentifier(); 
	 bool variableParameterSection(SemanticRecord&); 
	 bool whileStatement(); 
	 bool writeParameter(); 
	 bool writeParameterTail(); 
	 bool writeStatement();

};

#endif