#ifndef TEST_SCANNER_H
#define TEST_SCANNER_H

//-----------------------
// TestScanner 
//
// this contains unit tests for specific FSA that
// complicted enough to warrent them 
//----------------------=
class TestScanner
{

public:

	static bool testNumber();
	static bool testIdentifier();
	static bool testString();
	static bool testComment();

};

#endif //TEST_SCANNER_H