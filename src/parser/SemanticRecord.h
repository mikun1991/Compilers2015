#ifndef SEMANTICRECORD_H
#define SEMANTICRECORD_H

//#include "Operand.h"
//
//#include <string>
//#include <list>
//
////this class will hold the current semantic record and hold the current
////record until the record is complete and a call can be made to 
////one of the operators (like add)
//class SemanticOrganizer : SemanticRecord
//{
//
//public:
//	SemanticOrganizer();
//
//	//only call this at the begin of 
//	//the collecton of arguments  for a call to
//	//the semantic analyser.
//	void openRecord();
//	void insertOperand(Operand newOperand);
//
//	bool hasNext();
//	Operand nextOperand();
//
//	//this shoudl be callled in after all of the 
//	//arguments have been removed from the record
//	void closeRecord();
//
//private:
//	SemanticRecord* _currentRecord;
//};
//
//
////---------------------------------------------------
////  Semantic Record
////---------------------------------------------------
////These go back and forth between the parser and the semantic 
////anaylser carrying the variables needed to generate code
//class SemanticRecord
//{
//public:
//	SemanticRecord(SemanticRecord* referencing = NULL);
//
//	void insertOperand(Operand newOperand);
//
//	bool hasNext();
//	Operand nextOperand();
//
//
//protected:
//	SemanticRecord* referenced();
//	//this is a pointer to a Semanitc record 
//	//which need this value to complete
//	//keep this so it can return the address of its value
//	SemanticRecord* _referenceRecord;
//
//	std::list<Operand> _valuesInRecord;
//};

#include "Resources.h"
#include "Token.h"
#include "Lexeme.h"

#include <list>

class SemanticRecord{

public:
	void addId(Lexeme id);
	void setType(LexemeResources::DataType dataType);

	Lexeme getNextLexeme();
	Token getNextId();  // use this to iterate through the list of Ids
	Token showNextId(); // use this to return the first value but keep it in the list of Ids
	LexemeResources::DataType getType();

	int size();

private:
	std::list<Token> _identifiers;
	LexemeResources::DataType _type;

};

#endif //SEMANTICRECORD_H