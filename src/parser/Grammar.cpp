#include "Grammar.h"
#define	LOG( RULE , LOGGED) \
if (!LOGGED) logRule(RULE); LOGGED = true;

using namespace LexemeResources;
using namespace std;

void Grammar::setTokenStream(TokenStream* tokens)
{
	_currentTokens = tokens;
}

string Grammar::getError()
{
	string errors;
	for (string err : _errStrings){
		errors += err + "\n";
	}
	return errors;
}

//this is only used to move ahead to the next token
bool Grammar::match(){
	return _currentTokens->moveAhead();
}

//save a rule number in _ruleLog
void Grammar::logRule(int rule){
	_ruleLog.push_back(rule);
}

//print _ruleLog to std:out
void Grammar::printLog(){
	for (int& x : _ruleLog) std::cout << ' ' << x;
	std::cout << '\n';
}

void Grammar::error(string expectedTokenNames)
{
	//found
	Token next;
	_currentTokens->nextToken(next);

	string found(LexemeNames[(int)next.getType()]);
	int line = next.getLineNumber();
	int column = next.getColumnNumber();

	char buffer[200] = { 0 };
	sprintf(buffer, "ERROR - Expected %s found %s, at line %d and column %d!!", expectedTokenNames.c_str(), found.c_str(), line, column);


	_errStrings.push_back(string(buffer));
}

void Grammar::error(TypeList expectedTypes)
{
	return error(expectedTypes.asStr());
}

LexemeType Grammar::nextTokenType() const
{
	return _currentTokens->nextTokenType();
}

/*  Rule 99
Parses strings in the language generated by
<Factor> -> Integer|Float|String Literal|"True"|"False"|"not" <factor>|"(" <expression> ")"
			|<FunctionIdentifier> <OptionalActualParameterList> */
bool Grammar::factor()
{

	switch (nextTokenType())
	{
	case MP_FALSE: //103
		return match();
	case MP_NOT: //104
		return match();
	case MP_TRUE: //102
		return match();
	case MP_IDENTIFIER: //106
		functionIdentifier();
		return optionalActualParameterList();
	case MP_INTEGER_LIT: //99
		match();
	case MP_FLOAT_LIT: //100
		match();
	case MP_STRING_LIT: //101
		match();
	case MP_LPAREN: //105
		match();
	}

	match();
	return false;
}

/*  Rule 61
Parses strings in the language generated by
<ForStatement> -> "for" <ControlVariable> ":=" <InitialValue> <StepValue> <FinalValue> "do" <Statement> */
bool Grammar::forStatement()
{
	switch (nextTokenType())
	{
	case MP_FOR:
		match();
		controlVariable();
		assignmentStatement();
		initialValue();
		stepValue();
		finalValue();
		if (!(nextTokenType() == MP_DO)){
			error(asStr(MP_DO));
		}
		match();
		return statement();
	default:
		error(asStr(MP_FOR));
	}
	return false;
}

/*  Rule 94
Parses strings in the language generated by
<MultiplyingOperator> -> "*"|"/"|"div"|"mod"|"and"  */
bool Grammar::multiplyingOperator()
{
	switch (nextTokenType())
	{
	case MP_TIMES:
	case MP_FLOAT_DIVIDE:
	case MP_DIV:
	case MP_MOD:
	case MP_AND:
		//fall through to match
		return match();
	default:
		error( TypeList() << MP_TIMES << MP_FLOAT_DIVIDE << MP_DIV << MP_MOD << MP_AND );
	}
	return false;
}

/*  Rule 72
Parses strings in the language generated by
<ActualParameter> -> <OrdinalExpression> */
bool Grammar::actualParameter()
{
	switch (nextTokenType())
	{
	case MP_FALSE://72
	case MP_NOT: //72
	case MP_TRUE: //72
	case MP_IDENTIFIER://72
	case MP_INTEGER://72
	case MP_INTEGER_LIT://72
	case MP_FLOAT_LIT: //72
	case MP_STRING_LIT://72
	case MP_LPAREN://72
	case MP_MINUS://72
	case MP_PLUS:
		actualParameter();
		return ordinalExpression();
	default:
		error(TypeList() << MP_FALSE<< MP_NOT<< MP_TRUE<< MP_IDENTIFIER<< MP_INTEGER<< MP_INTEGER_LIT <<
			MP_FLOAT_LIT<< MP_STRING_LIT<< MP_LPAREN<< MP_MINUS << MP_PLUS );
	}
	return false;
}

/*  Rule 70
Parses strings in the language generated by
<ActualParameterTail> -> ","  <ActualParameter> <ActualParameterTail>
					  ->  E    */
bool Grammar::actualParameterTail()
{
	switch (nextTokenType())
	{
	case MP_COMMA://70
		match();
		actualParameter();
		return actualParameterTail();
	case MP_RPAREN://71
		return true; //follow set character
	default:
		error(TypeList() << MP_COMMA << MP_RPAREN );
	}
	return false;
}

/*  Rule 88
Parses strings in the language generated by
<AddingOperator> -> "+"|"-"|"or"  */
bool Grammar::addingOperator()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
		return match();
	case MP_MINUS:
		return match();
	case MP_OR:
		return match();
	default:
		error(TypeList() << MP_PLUS << MP_MINUS << MP_OR );
	}
	return false;
}

/*  Rule 54
Parses strings in the language generated by
<AssignmentStatement> ->  <VariableIdentifier> ":=" <Expression>
					  ->  <FunctionIdentifier> ":=" <Expression>       */
bool Grammar::assignmentStatement()
{
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		variableIdentifier();
		if (nextTokenType() != MP_ASSIGN){
			error(TypeList() << MP_ASSIGN );
		}
		match();
		return expression();
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 4
Parses strings in the language generated by
<Block> ->  <VariableDeclarationPart> <ProcedureAndFunctionDeclarationPart> <StatementPart>  */
bool Grammar::block()
{
	switch (nextTokenType())
	{
	case MP_BEGIN:
	case MP_VAR:
	case MP_FUNCTION:
	case MP_PROCEDURE:
		logRule(4);
		variableDeclarationPart();
		procedureAndFunctionDeclarationPart();
		statementPart();
	default:
		error(TypeList() << MP_BEGIN << MP_VAR << MP_FUNCTION << MP_PROCEDURE);
	}
	return false;
}

/*  Rule 111
Parses strings in the language generated by
<BooleanExpression> ->  <Expression> */
bool Grammar::booleanExpression()
{
	switch (nextTokenType())
	{
		//111
	case MP_FALSE:
	case MP_NOT:
	case MP_TRUE:
	case MP_IDENTIFIER:
	case MP_INTEGER:
	case MP_FIXED_LIT:
	case MP_STRING_LIT:
	case MP_LPAREN:
	case MP_MINUS:
	case MP_PLUS:
		expression();
		return true;
	default:
		error(TypeList() << MP_FALSE << MP_NOT << MP_TRUE 
			<< MP_IDENTIFIER << MP_INTEGER << MP_FIXED_LIT
			<< MP_STRING_LIT << MP_LPAREN << MP_MINUS << MP_PLUS );
	}
	return false;
}

/*  Rule 30
Parses strings in the language generated by
<CompoundStatement> -> "begin" <StatementSequence> "end" */
bool Grammar::compoundStatement()
{
	switch (nextTokenType())
	{
		//30
	case MP_BEGIN:
		match();
		statementSequence();
		if (nextTokenType() != MP_END){
			error(TypeList() << MP_END);
		}
		match();
		return true;
	default:
		error(TypeList() << MP_BEGIN);
	}
	return false;
}

/*  Rule 62
Parses strings in the language generated by
<ControlVariable> ->  <VariableIdentifier> */
bool Grammar::controlVariable()
{
	switch (nextTokenType())
	{
	//62 
	case MP_IDENTIFIER:
		variableIdentifier();
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 44
Parses strings in the language generated by
<EmptyStatement> ->  E   */
bool Grammar::emptyStatement()
{
	switch (nextTokenType())
	{
		//44
	case MP_END:
	case MP_UNTIL:
	case MP_SCOLON:
		return true; //Epsilon...
	default:
		error(TypeList() << MP_END << MP_UNTIL << MP_SCOLON);
	}
	return false;
}

/*  Rule 73
Parses strings in the language generated by
<Expression> ->  <SimpleExpression> [OptionalRelationalPart]  */
bool Grammar::expression()
{
	switch (nextTokenType())
	{
		//73
	case MP_PLUS:
	case MP_MINUS:
	case MP_LPAREN:
	case MP_STRING_LIT:
	case MP_IDENTIFIER:
	case MP_FIXED_LIT:
	case MP_FLOAT_LIT:
	case MP_TRUE:
	case MP_NOT:
	case MP_FALSE:
		simpleExpression();
		optionalRelationalPart();
		return true;
	default:
		error(TypeList());
	}
	return false;
}

/*  Rule 92
Parses strings in the language generated by
<FactorTail> ->  <MultiplyingOperator> <Factor> <FactorTail> 
			 ->  E    */
bool Grammar::factorTail()
{
	switch (nextTokenType())
	{
		//92
	case MP_AND:
	case MP_DIV:
	case MP_MOD:
	case MP_FLOAT_DIVIDE:
	case MP_TIMES:
		multiplyingOperator();
		factor();
		factorTail();
		return true;

	//TODO:: add cases here
		//93 (epsilon)

	default:
		error(TypeList());
	}
	return false;
}

/*  Rule 66
Parses strings in the language generated by
<FinalValue> ->  <OrdinalExpression> */
bool Grammar::finalValue()
{
	switch (nextTokenType())
	{
		//66
	case MP_FALSE:
	case MP_NOT:
	case MP_TRUE:
	case MP_IDENTIFIER:
	case MP_INTEGER_LIT:
	case MP_FLOAT_LIT:
	case MP_STRING_LIT:
	case MP_LPAREN:
	case MP_MINUS:
	case MP_PLUS:
		ordinalExpression();
		return true;
	default:
		error(TypeList() << MP_FALSE<< MP_NOT<< MP_IDENTIFIER<< MP_INTEGER_LIT<< 
			MP_FLOAT_LIT<< MP_STRING_LIT<< MP_LPAREN<< MP_MINUS<< MP_PLUS);
	}
	return false;
}

/*  Rule 25
Parses strings in the language generated by
<FormalParameterSection> ->  <ValueParameterSection> | <VariableParameterSection>  */
bool Grammar::formalParameterSection()
{
	switch (nextTokenType())
	{
		//25
	case MP_IDENTIFIER:
		valueParameterSection();
		return true;

		//26
	case MP_VAR:
		variableParameterSection();
		return true;

	default:
		error(TypeList() << MP_IDENTIFIER << MP_VAR);
	}
	return false;
}

/*  Rule 23
Parses strings in the language generated by
<FormalParameterSectionTail> ->  ";" <FormalParameterSection> <FormalParameterSectionTail>
							 ->  E	*/
bool Grammar::formalParameterSectionTail()
{
	switch (nextTokenType())
	{
		//24
		case MP_SCOLON:
			logRule(24);
			formalParameterSection();
			formalParameterSectionTail();

			return true;
		//25
		case MP_RPAREN:
			logRule(25);
			return true; //epsilon

	default:
		error(TypeList() << MP_RPAREN << MP_SCOLON);
	}
	return false;
}

/*  Rule 18
Parses strings in the language generated by
<FunctionDeclaration> -> <FunctionHeading> ";" <Block> ";" */
bool Grammar::functionDeclaration()
{
	switch (nextTokenType())
	{
	case MP_FUNCTION:
		logRule(18);
		functionHeading();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
		}
		else{
			match();
			block();
			if (nextTokenType() != MP_SCOLON){
				error(TypeList() << MP_SCOLON);
			}
			else {
				match();
				return true;
			}
		}
	default:
		error(TypeList() << MP_FUNCTION);
	}
	return false;
}

/*  Rule 20
Parses strings in the language generated by
<FunctionHeading> ->  "function" <functionIdentifier> [OptionalFormalParameterList] ":" <Type> */
bool Grammar::functionHeading()
{
	switch (nextTokenType())
	{
		//20
	case MP_FUNCTION:
		logRule(20);
		match();
		functionIdentifier();
		optionalFormalParameterList();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
		}
		match();
		type();

		return true;
	default:
		error(TypeList() << MP_FUNCTION);

	}
	return false;
}

/*  Rule 110
Parses strings in the language generated by
<FunctionIdentifier> ->  identifier */
bool Grammar::functionIdentifier()
{

	switch (nextTokenType())
	{
	//110
	case MP_IDENTIFIER:
		logRule(110);
		match();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 113
Parses strings in the language generated by
<IdentifierList> -> identifier <IdentifierTail> */
bool Grammar::identifierList()
{

	switch (nextTokenType())
	{
	//113
	case MP_IDENTIFIER:
		logRule(113);
		match();
		identifierTail();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 114
Parses strings in the language generated by
<IdentifierTail> -> "," identifier <IdentifierTail>
				 ->  E	*/
bool Grammar::identifierTail()
{
	switch (nextTokenType())
	{
		//114
	case MP_COMMA:
		logRule(114);
		match();
		if (nextTokenType() != MP_IDENTIFIER){
			error(TypeList() << MP_IDENTIFIER);
		}
		match();
		identifierTail();
		return true;

		//epsilon - 115
	case MP_COLON:
		logRule(115);
		return true;

	default:
		error(TypeList() << MP_COMMA << MP_COLON);
	}
	return false;
}

/*  Rule 56
Parses strings in the language generated by
<IfStatement> -> "if" <BooleanExpression> "then" <Statement> [OptionalElsePart] */
bool Grammar::ifStatement()
{
	switch (nextTokenType())
	{
		//56
	case MP_IF:
		logRule(56);
		match();
		booleanExpression();
		if (nextTokenType() != MP_THEN){
			error(TypeList() << MP_THEN);
		}
		match();
		statement();
		optionalElsePart();
		return true;

	default:
		error(TypeList() << MP_IF);
	}
	return false;
}

/*  Rule 63
Parses strings in the language generated by
<InitialValue> -> <OrdinalExpression> */
bool Grammar::initialValue()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
	case MP_LPAREN:
	case MP_FALSE:
	case MP_TRUE:
	case MP_IDENTIFIER:
	case MP_NOT:
	case MP_STRING_LIT:
	case MP_FLOAT_LIT:
	case MP_INTEGER_LIT:
		logRule(63);
		ordinalExpression();
		return true;
	default:
		error(TypeList() << MP_PLUS << MP_MINUS << MP_LPAREN << MP_FALSE << MP_TRUE << MP_IDENTIFIER << MP_NOT << MP_STRING_LIT << MP_FLOAT_LIT << MP_INTEGER_LIT);
	}
	return false;
}

/*  Rule 68
Parses strings in the language generated by
<OptionalActualParameterList> -> "(" <ActualParameter> <ActualParameterTail> ")" 
							  ->  E		*/
bool Grammar::optionalActualParameterList()
{
	switch (nextTokenType())
	{
		case MP_LPAREN:
			actualParameter();
			actualParameterTail();
			MP_RPAREN;
			return match();
		default:
			error("Error");
	}
	return false;
}

/*  Rule 57
Parses strings in the language generated by
<OptionalElsePart> -> "else" <Statement> 
				   ->  E	*/
bool Grammar::optionalElsePart()
{
	switch (nextTokenType())
	{
	case MP_ELSE:
		match();
		return statement();
	default:
		error("else");
	}
	return false;
}

/*  Rule 21
Parses strings in the language generated by
<OptionalFormalParameterList> -> "(" <FormalParameterSection> <FormalParameterSectionTail> ")" 
							  ->  E		*/
bool Grammar::optionalFormalParameterList()
{
	switch (nextTokenType())
	{
	case MP_LPAREN:
		match();
		formalParameterSection();
		formalParameterSectionTail();
		if (nextTokenType() != MP_RPAREN){
			error(TypeList() << MP_RPAREN);
		}
		match();
	default: //epsilon
		//TODO: add correct follow et 
		return true;
	}
}

/*  Rule 74
Parses strings in the language generated by
<OptionalRelationalPart> -> <RelationalOperator> <SimpleExpression>
						 ->  E    */
bool Grammar::optionalRelationalPart()
{
	switch (nextTokenType())
	{
	case MP_EQUAL:
	case MP_LTHAN:
	case MP_GTHAN:
	case MP_LEQUAL:
	case MP_GEQUAL:
	case MP_NEQUAL:
		relationalOperator();
		return simpleExpression();
	default:
		error("Error");
	}
	return false;
}

/*  Rule 85
Parses strings in the language generated by
<OptionalSign> -> "+"|"-"| E   */
bool Grammar::optionalSign()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
		return match();
	default:
		error("Sign");
	}
	return false;
}

/*  Rule 112
Parses strings in the language generated by
<OrdinalExpression> -> <Expression> */
bool Grammar::ordinalExpression()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
		expression();
		return true;
	default:
		error("Error");
	}
	return false;
}

/*  Rule 14
Parses strings in the language generated by
<ProcedureAndFunctionDeclarationPart> -> <ProcedureDeclaration> <ProcedureAndFunctionDeclarationPart>
									  -> <FunctionDeclaration> <ProcedureAndFunctionDeclarationPart>  */
bool Grammar::procedureAndFunctionDeclarationPart()
{
	switch (nextTokenType())
	{
	case MP_PROCEDURE:
		procedureDeclaration();
		return procedureAndFunctionDeclarationPart();
	case MP_FUNCTION:
		functionDeclaration();
		return procedureAndFunctionDeclarationPart();
	default:
		error("Error");
	}

	return false;
}

/*  Rule 17
Parses strings in the language generated by
<ProcedureDeclaration> -> <ProcedureHeading> ";" <Block> ";" */
bool Grammar::procedureDeclaration()
{
	switch (nextTokenType())
	{
	case MP_PROCEDURE:
		procedureHeading();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
		}
		match();
		block();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
		}
		match();
		return true;
	default:
		error(TypeList() << MP_PROCEDURE);
	}
	return false;
}

/*  Rule 19
Parses strings in the language generated by
<ProcedureHeading> -> "procedure" <procedureIdentifier> [OptionalFormalParameterList] */
bool Grammar::procedureHeading()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_PROCEDURE:
		LOG(19 , logged)
		match(); //match "procedure"
		procedureIdentifier();
		optionalFormalParameterList();
	default:
		error(TypeList() << MP_PROCEDURE);
	}
	return false;
}

/*  Rule 109
Parses strings in the language generated by
<ProcedureIdentifier> -> identifier */
bool Grammar::procedureIdentifier()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		LOG(109, logged)
		match();//
		return true;
	default:
		error("Error");
	}
	return false;
}

/*  Rule 67
Parses strings in the language generated by
<ProcedureStatement> -> <ProcedureIdentifier> [OptionalActualParameterList] */
bool Grammar::procedureStatement()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		LOG(67, logged);
		procedureIdentifier();
		optionalActualParameterList();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 2
Parses strings in the language generated by
<Program> -> <ProgramHeading> ";" <Block> "." */
bool Grammar::program()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_PROGRAM:
		LOG(2, logged);
		programHeading();
		if (nextTokenType() != MP_SCOLON)
		{
			error(TypeList() << MP_SCOLON);
		}
		match();
		block();
		if (nextTokenType() == MP_PERIOD){
			error(TypeList() << MP_PERIOD);
		}
		match();
		return true;

	default:
		error(TypeList() << MP_PROGRAM);
		return false;
	}
}

/*  Rule 3
Parses strings in the language generated by
<ProgramHeading> -> "program" <ProgramIdentifier> */
bool Grammar::programHeading()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_PROGRAM:
		LOG(3, logged);
		match();
		programIdentifier();
		return true;
	default:
		error(TypeList() << MP_PROGRAM);
	}
	return false;
}

/*  Rule 107
Parses strings in the language generated by
<ProgramIdentifier> -> identifier */
bool Grammar::programIdentifier()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		LOG(107, logged);
		match();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 48
Parses strings in the language generated by
<ReadParameter> -> <VariableIdentifier> */
bool Grammar::readParameter()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		LOG(48, logged);
		variableIdentifier();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 46
Parses strings in the language generated by
<ReadParameterTail> -> "," <ReadParameter> <ReadParameterTail> */
bool Grammar::readParameterTail()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_COMMA:
		LOG(46, logged);
		match();
		readParameter();
		readParameterTail();
		return true;
		break;
	case MP_RPAREN: //follow set (epsilon)
		return true;
	default:
		error(TypeList() << MP_COMMA);
	}
	return false;
}

/*  Rule 45
Parses strings in the language generated by
<ReadStatement> -> "read" "(" <ReadParameter> <ReadParameterTail> ")" */
bool Grammar::readStatement()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_READ:
		LOG(45, logged);
		match(); // match "read"
		if (nextTokenType() != MP_LPAREN){
			error(TypeList() << MP_LPAREN);
		}
		match();
		readParameter();
		readParameterTail();
		if (nextTokenType() != MP_RPAREN){
			error(TypeList() << MP_RPAREN);
		}
		match();
		return true;
		break;
	default:
		error(TypeList() << MP_READ);
	}
	return false;
}

/*  Rule 76
Parses strings in the language generated by
<RelationalOperator> -> "="|"<"|">"|"<="|">="|"<>" */
bool Grammar::relationalOperator()
{ 
	bool logged = false;

	switch (nextTokenType())
	{
	case MP_EQUAL:
		LOG(76, logged);
	case MP_LTHAN:
		LOG(77, logged);
	case MP_GTHAN:
		LOG(78, logged);
	case MP_LEQUAL:
		LOG(79, logged);
	case MP_GEQUAL:
		LOG(80, logged);
	case MP_NEQUAL:
		LOG(81, logged);
		match();
		return true;
	default:
		error(TypeList() << MP_EQUAL << MP_LTHAN << MP_GTHAN << MP_LEQUAL << MP_GEQUAL << MP_NEQUAL);
	}
	return false;
}

/*  Rule 59
Parses strings in the language generated by
<RepeatStatement> -> "repeat" <StatementSequence> "until" <BooleanExpression>    */
bool Grammar::repeatStatement()
{
	bool logged = false;

	switch (nextTokenType())
	{
	case MP_REPEAT:
		LOG(59, logged)
		match();
		;		statementSequence();
		if (nextTokenType() != MP_UNTIL){
			error(TypeList() << MP_UNTIL);
		}
		match();
		booleanExpression();
		return true;
		break;
	default:
		error(TypeList() << MP_REPEAT);	
	}

	return false;
}

/*  Rule 82
	Parses strings in the language generated by 
	<SimpleExpression> -> [ OptionalSign ] <Term> <TermTail>   */
bool Grammar::simpleExpression()
{
	bool logged = false;

	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
	case MP_INTEGER_LIT:
	case MP_FLOAT_LIT:
	case MP_STRING_LIT:
	case MP_NOT:
	case MP_LPAREN:
	case MP_IDENTIFIER:
	case MP_FALSE:
	case MP_TRUE:
		//all of the above cases fall through to parse <Term> <TermTail>
		LOG(82, logged);
		optionalSign();
		term();
		termTail();
		return true;
	default:
		//Everythng else fails
		error(TypeList() << MP_PLUS << MP_MINUS << MP_INTEGER_LIT << MP_FLOAT_LIT 
			<< MP_STRING_LIT  << MP_NOT << MP_LPAREN << MP_IDENTIFIER << MP_FALSE <<MP_TRUE);
		return false;
	}

}

/*  Rule 34
Parses strings in the language generated by
<Statement> -> <EmptyStatement>|<CompoundStatment>|<ReadStatement>|<WriteStatement>|<AssignmentStatment>|
				<IfStatement>|<WhileStatement>|<RepeatStatement>|<ForStatement>|<ProcedureStatement> */
bool Grammar::statement()
{
	bool logged = false;

	switch (nextTokenType())
	{
	case MP_BEGIN:
		LOG(35, logged);
		return compoundStatement();
		break;

	case MP_ELSE:
	case MP_END:
		LOG(36, logged);
		return emptyStatement();
		break;

	case MP_FOR:
		LOG(42, logged)
		return forStatement();
		break;

	case MP_IF:
		LOG(39, logged);
		return ifStatement();
		break;

	case MP_PROCEDURE:
		LOG(43, logged);
		return procedureStatement();
		break;

	case MP_READ:
		LOG(36, logged);
		return readStatement();
		break;

	case MP_REPEAT:
		LOG(41, logged);
		return repeatStatement();
		break;

	case MP_UNTIL:
		LOG(34, logged);
		return emptyStatement();
		break;

	case MP_WHILE:
		LOG(40, logged);
		return whileStatement();
		break;

	case MP_WRITELN:
	case MP_WRITE:
		LOG(37, logged);
		return forStatement();
		break;

	case MP_IDENTIFIER:  // AMBIGUITY IN LL1 TABLE 38 or 43
		LOG(38, logged);
		return assignmentStatement();
		break;

	default:
		error(TypeList() << MP_BEGIN << MP_ELSE << MP_END << MP_FOR << MP_IF << MP_PROCEDURE
			<< MP_READ << MP_REPEAT << MP_UNTIL <<MP_WHILE << MP_WRITELN << MP_WRITE << MP_IDENTIFIER);

	}

	return false;
}

/*  Rule 29
Parses strings in the language generated by
<StatementPart> -> <CompoundStatement> */
bool Grammar::statementPart()
{
	bool logged = false;
	
	switch (nextTokenType())
	{
	case MP_BEGIN:
		LOG(29, logged);
		return compoundStatement();
		break;

	default:
		error(TypeList() << MP_BEGIN);
	}

	return false;
}

/*  Rule 31
Parses strings in the language generated by
<StatementSequence> -> <Statement> <StatementTail> */
bool Grammar::statementSequence()
{
	bool logged = false;

	switch (nextTokenType())
	{
	case MP_BEGIN:
	case MP_END:
	case MP_FOR:
	case MP_IF:
	case MP_READ:
	case MP_REPEAT:
	case MP_UNTIL:
	case MP_WHILE:
	case MP_WRITE:
	case MP_WRITELN:
	case MP_IDENTIFIER:
	case MP_SCOLON:
		LOG(31, logged);
		statement();
		return statementTail();

	default:
		error(TypeList() << MP_BEGIN  << MP_END << MP_FOR << MP_IF << MP_READ << MP_REPEAT 
			<< MP_UNTIL << MP_WHILE << MP_WRITE << MP_WRITELN << MP_IDENTIFIER << MP_SCOLON );
	}
	return false;
}

/*  Rule 32
Parses strings in the language generated by
<StatementTail> -> ";" <Statement> <StatementTail>
				-> E */
bool Grammar::statementTail()
{
	bool logged = false;
	switch (nextTokenType())
	{
	case MP_SCOLON:
		LOG(32, logged);
		match();
		statement();
		return statementTail();
		break;

	case MP_END://follow set of epsilon
	case MP_UNTIL:
		LOG(33, logged);
	
	default:
		error(TypeList() << MP_SCOLON << MP_END << MP_UNTIL);
	}

	return false;
}

/*  Rule 64
Parses strings in the language generated by
<StepValue> -> "to" | "downto" */
bool Grammar::stepValue()
{
	switch (nextTokenType())
	{
	case MP_TO:
		logRule(64);
		return match();
		break;
	case MP_DOWNTO:
		logRule(65);
		return match();
		break;
	default:
		error(TypeList() << MP_TO << MP_DOWNTO );
	}
	return false;
}

/*  Rule 1
Parses strings in the language generated by
<SystemGoal> -> <Program> EOF */
bool Grammar::systemGoal()
{
	switch (nextTokenType())
	{
	case MP_PROGRAM:
		logRule(1);
		program();
		if (nextTokenType() == MP_EOF)
		{
			return true;
		}
	default:
		error(TypeList() << MP_PROGRAM );
	}
	return false;
}

/*  Rule 91
Parses strings in the language generated by
<Term> -> <Factor> <FactorTail> */
bool Grammar::term()
{
	switch (nextTokenType())
	{
	case MP_INTEGER_LIT:
	case MP_FLOAT_LIT:
	case MP_STRING_LIT:
	case MP_BOOLEAN:
	case MP_NOT:
	case MP_LPAREN:
	case MP_IDENTIFIER:
		//all of the above cases fall through to parse <Factor> <FactorTail>
		factor();
		return factorTail();

	default:
		//Everythng else fails
		error(TypeList() << MP_INTEGER << MP_FLOAT << MP_STRING << MP_BOOLEAN << MP_NOT << MP_LPAREN << MP_IDENTIFIER);
		return false;
	}
}

/*  Rule 83
Parses strings in the language generated by
<TermTail> -> <AddingOperator> <Term> <TermTail> */
bool Grammar::termTail()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
	case MP_OR:
		addingOperator();
		term();
		return termTail();
	default:
		error(TypeList() << MP_PLUS << MP_MINUS << MP_OR);
	}
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
		error(TypeList() << MP_INTEGER << MP_BOOLEAN << MP_FLOAT << MP_STRING );
	}

	return false;
}

/*  Rule 27
Parses strings in the language generated by
<ValueParameterSection> -> <IdentifierList> ":" <Type> */
bool Grammar::valueParameterSection()
{
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		identifierList();
		if (nextTokenType() == MP_COLON)
		{
			return type();
		}
		else {
			error(TypeList() << MP_COLON);
			return false;
		}
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 9
Parses strings in the language generated by
<VariableDeclaration> -> <IdentifierList> ":" <Type> */
bool Grammar::variableDeclaration()
{
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		identifierList();
		if (nextTokenType() != MP_COLON){
			error(TypeList() << MP_COLON);
		}
		match();
		return type();
	default:
		error(TypeList() << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 5
Parses strings in the language generated by
<VariableDeclarationPart> -> "var" <VariableDeclaration> ";" <VariableDeclarationTail>
						  ->  E  */
bool Grammar::variableDeclarationPart()
{
	switch (nextTokenType())
	{
	case MP_VAR:
		match();
		variableDeclaration();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
		}
		match();
		variableDeclarationTail();
		return true;
	default:  // epsilon
		return true;
	}
}

/*  Rule 7
Parses strings in the language generated by
<VariableDeclarationTail> -> <VariableDeclaration> ";" <VariableDeclarationTail> */
bool Grammar::variableDeclarationTail()
{
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		variableDeclaration();
		if (nextTokenType() != MP_SCOLON){
			error(TypeList() << MP_SCOLON);
			return false;
		}
		else {
			match();
			variableDeclarationTail();
			return true;
		}
	case MP_VAR:
		variableDeclarationTail();
		return true;
	default:
		//epsilon 
		//error(TypeList() << MP_IDENTIFIER);
		return false;
	}
}

/*  Rule 108
Parses strings in the language generated by
<VariableIdentifier> -> Identifier */
bool Grammar::variableIdentifier()
{
	switch (nextTokenType())
	{
	case MP_IDENTIFIER:
		match();
		return true;
	default:
		error(TypeList() << MP_IDENTIFIER);
		return false;
	}
}

/*  Rule 28
Parses strings in the language generated by
<VariableParameterSection> -> "var" <IdentifierList> ":" <Type>  */
bool Grammar::variableParameterSection()
{
	switch (nextTokenType())
	{
	case MP_VAR:
		match();
		identifierList();
		if (nextTokenType() != MP_COLON){
			error(TypeList() << MP_COLON);
			return false;
		}
		else {
			match();
			type();
			return true;
		}
	default:
		error(TypeList() << MP_VAR);
		return false;
	}
}

/*  Rule 60
Parses strings in the language generated by
<WhileStatement> -> "while" <BooleanExpression> "do" <Statement> */
bool Grammar::whileStatement()
{
	switch (nextTokenType())
	{
	case MP_WHILE:
		match();
		booleanExpression();
		if (nextTokenType() != MP_DO){
			error(TypeList() << MP_DO);
			return false;
		}
		else {
			match();
			statement();
			return true;
		}
	default:
		error(TypeList() << MP_WHILE);
		return false;
	}
}

/*  Rule 53
Parses strings in the language generated by
<WriteParameter> -> <OrdinalExpression>   */
bool Grammar::writeParameter()
{
	switch (nextTokenType())
	{
	case MP_PLUS:
	case MP_MINUS:
	case MP_INTEGER_LIT:
	case MP_FLOAT_LIT:
	case MP_STRING_LIT:
	case MP_BOOLEAN:
	case MP_NOT:
	case MP_LPAREN:
	case MP_IDENTIFIER:
		ordinalExpression();
		return true;
	default:
		error(TypeList() << MP_PLUS << MP_MINUS << MP_INTEGER_LIT << MP_FLOAT_LIT << MP_STRING_LIT << MP_BOOLEAN << MP_NOT << MP_LPAREN << MP_IDENTIFIER);
	}
	return false;
}

/*  Rule 51
Parses strings in the language generated by
<WriteParameterTail> -> "," <WriteParameter> <WriteParameterTail>
					 ->  E  */
bool Grammar::writeParameterTail()
{
	switch (nextTokenType())
	{
	case MP_COMMA:
		match();
		writeParameter();
		writeParameterTail();
		return true;
	default:
		return true;
	}
	return false;
}

/*  Rule 49
Parses strings in the language generated by
<WriteStatement> -> "write"  "(" <WriteParameter> <WriteParameterTail> ")" 
				 -> "writeln" "(" <WriteParameter> <WriteParameterTail> ")"  */
bool Grammar::writeStatement()
{
	switch (nextTokenType())
	{
	case MP_WRITE:
	case MP_WRITELN:
		match();
		if (nextTokenType() != MP_LPAREN){
			error(TypeList() << MP_LPAREN);
			return false;
		}
		else {
			match();
			writeParameter();
			writeParameterTail();
			if (nextTokenType() != MP_RPAREN){
				error(TypeList() << MP_RPAREN);
				return false;
			}
			else {
				match();
				return true;
			}
		}
	default:
		error(TypeList() << MP_WRITE << MP_WRITELN);
		return false;
	}
}