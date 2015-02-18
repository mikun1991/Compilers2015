#include "Grammar.h"

using namespace LexemeResources;
using namespace std;

Scanner _currentScanner;  //this will be constructed with a filepath
Token _lookAheadToken = _currentScanner.getNextToken(); //this will be set by Scanner's getNextToken()


bool match(LexemeType type){
	if (_lookAheadToken.getLexeme().getType() == type){
		_lookAheadToken = _currentScanner.getNextToken();
		return true;
	}
	else {
		error(_lookAheadToken.getLineNumber(), _lookAheadToken.getColumnNumber());
		return false;
	}
}


void error(int errorLine, int errorColumn){
	//print error message
	//recover
}


bool Grammar::factor()
{
	std::string value = _lookAheadToken.getLexeme().getValue();

	
	//switch (_lookAheadToken.getLexeme().getType())
	//{
	//	case Lexeme::
	//}

	return false;
}

bool Grammar::forStatement()
{

	return false;
}

bool Grammar::multiplyingOperator()
{

	return false;
}

bool Grammar::actualParameter()
{

	return false;
}

bool Grammar::actualParameterTail()
{

	return false;
}

bool Grammar::addingOperator()
{

	return false;
}

bool Grammar::assignmentStatement()
{

	return false;
}

bool Grammar::block()
{

	return false;
}

bool Grammar::booleanExpression()
{

	return false;
}

bool Grammar::compoundStatement()
{

	return false;
}

bool Grammar::controlVariable()
{

	return false;
}

bool Grammar::emptyStatement()
{

	return false;
}

bool Grammar::expression()
{

	return false;
}

bool Grammar::factorTail()
{

	return false;
}

bool Grammar::finalValue()
{

	return false;
}

bool Grammar::formalParameterSection()
{

	return false;
}

bool Grammar::formalParameterSectionTail()
{

	return false;
}

bool Grammar::functionDeclaration()
{

	return false;
}

bool Grammar::functionHeading()
{

	return false;
}

bool Grammar::functionIdentifier()
{

	return false;
}

bool Grammar::identifierList()
{

	return false;
}

bool Grammar::identifierTail()
{

	return false;
}

bool Grammar::ifStatement()
{

	return false;
}

bool Grammar::initialValue()
{

	return false;
}

bool Grammar::optionalActualParameterList()
{

	return false;
}

bool Grammar::optionalElsePart()
{

	return false;
}

bool Grammar::optionalFormalParameterList()
{

	return false;
}

bool Grammar::optionalRelationalPart()
{

	return false;
}

bool Grammar::optionalSign()
{

	return false;
}

bool Grammar::ordinalExpression()
{

	return false;
}

bool Grammar::procedureAndFunctionDeclarationPart()
{

	return false;
}

bool Grammar::procedureDeclaration()
{

	return false;
}

bool Grammar::procedureHeading()
{

	return false;
}

bool Grammar::procedureIdentifier()
{

	return false;
}

bool Grammar::procedureStatement()
{

	return false;
}

bool Grammar::program()
{
	if (!programHeading()){
		return false;
	}

//check if the next if next is ;

	//ce

	return false;
}

bool Grammar::programHeading()
{

	return false;
}

bool Grammar::programIdentifier()
{

	return false;
}

bool Grammar::readParameter()
{

	return false;
}

bool Grammar::readParameterTail()
{

	return false;
}

bool Grammar::readStatement()
{

	return false;
}

bool Grammar::relationalOperator()
{

	return false;
}

bool Grammar::repeatStatement()
{

	return false;
}

bool Grammar::simpleExpression()
{
	switch (_lookAheadToken.getLexeme().getType()){
	case LexemeType::MP_PLUS:
		match(LexemeType::MP_PLUS);
		break;
	case LexemeType::MP_MINUS:
		match(LexemeType::MP_MINUS);
		break;
	default:
		if (term()){
			return termTail();
		}
	}
	return false;

	/*  Possible alternate implementation?
	
	std::string value = _lookAheadToken.getLexeme().getValue();
	if (value == "+"){
		match(LexemeType::MP_PLUS);
	}
	else if (value == "-"){
		match(LexemeType::MP_MINUS);
	}
	term();
	while (value == "+"){
		term();
	}
	
	*/
}

bool Grammar::statement()
{

	return false;
}

bool Grammar::statementPart()
{

	return false;
}

bool Grammar::statementSequence()
{

	return false;
}

bool Grammar::statementTail()
{

	return false;
}

bool Grammar::stepValue()
{

	return false;
}

bool Grammar::systemGoal()
{

	return false;
}

bool Grammar::term()
{

	return false;
}

bool Grammar::termTail()
{

	return false;
}

bool Grammar::type()
{

	return false;
}

bool Grammar::valueParameterSection()
{

	return false;
}

bool Grammar::variableDeclaration()
{

	return false;
}

bool Grammar::variableDeclarationPart()
{

	return false;
}

bool Grammar::variableDeclarationTail()
{

	return false;
}

bool Grammar::variableIdentifier()
{

	return false;
}

bool Grammar::variableParameterSection()
{

	return false;
}

bool Grammar::whileStatement()
{

	return false;
}

bool Grammar::writeParameter()
{

	return false;
}

bool Grammar::writeParameterTail()
{

	return false;
}

bool Grammar::writeStatement()
{

	return false;
}

