#include "Grammar.h"

using namespace LexemeResources;
using namespace std;


//this is only used to move ahead to the next token
bool Grammar::match(){
	return _currentTokens.moveAhead();
}


void Grammar::error(string expectedTokenNames)
{
	//found
	Token next;
	_currentTokens.nextToken(next);

	string found(LexemeNames[(int)next.getType()]);
	int line = next.getLineNumber();
	int column = next.getColumnNumber();

	char buffer[200] = { 0 };
	sprintf(buffer, "ERROR - Expected %s found %s, at line %d and column %d!!", expectedTokenNames.c_str(), found.c_str(), line, column);

	_errString = string(buffer);
}


LexemeType Grammar::nextTokenType() const
{
	return _currentTokens.nextTokenType();
}

bool Grammar::factor()
{

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

/*  Rule 82
	Parses strings in the language generated by 
	<SimpleExpression> -> [ Sign ] <Term> <TermTail> */
bool Grammar::simpleExpression()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
		match();
	}

	switch (nextTokenType())
	{
	case MP_INTEGER_LIT:
	case MP_FLOAT_LIT:
	case MP_STRING_LIT:
	case MP_BOOLEAN:
	case MP_NOT:
	case MP_LPAREN:
	case MP_IDENTIFIER:
		//all of the above cases fall through to parse <Term> <TermTail>
		term();
		return termTail();

	default:
		//Everythng else fails
		error("Sign Integer Float String Boolean Not LParen Identifier");
		return false;
	}

}

/*  Rule 34
Parses strings in the language generated by
<Statement> -> <EmptyStatement>|<CompoundStatment>|<ReadStatement>|<WriteStatement>|<AssignmentStatment>|
				<IfStatement>|<WhileStatement>|<RepeatStatement>|<ForStatement>|<ProcedureStatement> */
bool Grammar::statement()
{
	switch (nextTokenType())
	{
	case MP_BEGIN:
		return compoundStatement();
	case MP_READ:
		return readStatement();
	case MP_WRITE:
		return writeStatement();
	case MP_IF:
		return ifStatement();
	case MP_WHILE:
		return whileStatement();
	case MP_REPEAT:
		return repeatStatement();
	case MP_FOR:
		return forStatement();
	case MP_IDENTIFIER:
		assignmentStatement();
		procedureStatement();
	default:
		error("Begin, Read, Write, Writeln, If, While, Repeat, For, Identifier");
	}
	return false;
}

/*  Rule 29
Parses strings in the language generated by
<StatementPart> -> <CompoundStatement> */
bool Grammar::statementPart()
{

	return false;
}

/*  Rule 31
Parses strings in the language generated by
<StatementSequence> -> <Statement> <StatementTail> */
bool Grammar::statementSequence()
{

	return false;
}

/*  Rule 32
Parses strings in the language generated by
<StatementTail> -> ";" <Statement> <StatementTail>
				-> E */
bool Grammar::statementTail()
{

	return false;
}

/*  Rule 64
Parses strings in the language generated by
<StepValue> -> "to" | "downto" */
bool Grammar::stepValue()
{

	return false;
}

/*  Rule 1
Parses strings in the language generated by
<SystemGoal> -> <Program> EOF */
bool Grammar::systemGoal()
{

	return false;
}

/*  Rule 91
Parses strings in the language generated by
<Term> -> <Factor> <FactorTail> */
bool Grammar::term()
{

	return false;
}

/*  Rule 83
Parses strings in the language generated by
<TermTail> -> <AddingOperator> <Term> <TermTail> */
bool Grammar::termTail()
{

	return false;
}

/*  Rule 10
Parses strings in the language generated by
<Type> -> "Integer"|"Float"|"String"|"Boolean" */
bool Grammar::type()
{

	switch (nextTokenType())
	{
	case MP_INTEGER:
	case MP_BOOLEAN:
	case MP_FLOAT:
	case MP_STRING:
		//all of the above cases fall through to accept
		return match();

	default:
		//Everythng else fails
		error("Type");
	}

	return false;
}

/*  Rule 27
Parses strings in the language generated by
<ValueParameterSection> -> <IdentifierList> ":" <Type> */
bool Grammar::valueParameterSection()
{

	return false;
}

/*  Rule 9
Parses strings in the language generated by
<VariableDeclaration> -> <IdentifierList> ":" <Type> */
bool Grammar::variableDeclaration()
{

	return false;
}

/*  Rule 5
Parses strings in the language generated by
<VariableDeclarationPart> -> "var" <VariableDeclaration> ";" <VariableDeclarationTail>
						  ->  E  */
bool Grammar::variableDeclarationPart()
{

	return false;
}

/*  Rule 7
Parses strings in the language generated by
<VariableDeclarationTail> -> <VariableDeclaration> ";" <VariableDeclarationTail> */
bool Grammar::variableDeclarationTail()
{

	return false;
}

/*  Rule 108
Parses strings in the language generated by
<VariableIdentifier> -> Identifier */
bool Grammar::variableIdentifier()
{

	return false;
}

/*  Rule 28
Parses strings in the language generated by
<VariableParameterSEction> -> "var" <IdentifierList> ":" <Type>  */
bool Grammar::variableParameterSection()
{

	return false;
}

/*  Rule 60
Parses strings in the language generated by
<WhileStatement> -> "while" <BooleanExpression> "do" <Statement> */
bool Grammar::whileStatement()
{

	return false;
}

/*  Rule 53
Parses strings in the language generated by
<WriteParameter> -> <OrdinalExpression>   */
bool Grammar::writeParameter()
{

	return false;
}

/*  Rule 51
Parses strings in the language generated by
<WriteParameterTail> -> "," <WriteParameter> <WriteParameterTail>
					 ->  E  */
bool Grammar::writeParameterTail()
{

	return false;
}

/*  Rule 49
Parses strings in the language generated by
<WriteStatement> -> "write"  "(" <WriteParameter> <WriteParameterTail> ")" 
				 -> "writeln" "(" <WriteParameter> <WriteParameterTail> ")"  */
bool Grammar::writeStatement()
{

	return false;
}

