#include "SemanticRecord.h"

#include <assert.h>


SemanticOrganizer::SemanticOrganizer()
{
	_currentRecord = NULL;
}

void SemanticOrganizer::openRecord()
{
	_currentRecord = new SemanticRecord(_currentRecord);
}

void SemanticOrganizer::insertOperand(Operand newOperand)
{ 
	assert(_currentRecord);
	_currentRecord->insertOperand(newOperand);
}


bool SemanticOrganizer::hasNext()
{
	_currentRecord->hasNext();
}

void SemanticOrganizer::closeRecord()
{
	SemanticRecord* nextUp = _currentRecord->referenced();
	delete _currentRecord;
	_currentRecord = nextUp;
}


SemanticRecord::SemanticRecord(SemanticRecord * referencing)
{
	_referenceRecord = referencing;
}

void SemanticRecord::insertOperand(Operand newOperand)
{

}

bool SemanticRecord::hasNext()
{
	return _valuesInRecord.empty();
}

Operand SemanticRecord::nextOperand()
{
	return _valuesInRecord.front();
	_valuesInRecord.pop_front();
}

SemanticRecord* SemanticRecord::referenced()
{
	return _referenceRecord;
}
