
>-------------------< Micro Pascal Compiler >-----------------------<



*** The Project requires CMake version 3 or higheriun order to build ***


//
// Make Scripts
//

The project can be built to a visual studio 2013 project with the make_windows bat scripts (64 for 64bit project)

The project can be built for to a eclipse (c++) file on linux/mac with the make_ecplise shell script

make_unix executable will build the binary executable on linux/mac which can be run from the command prompt


//
// Files
//


** scr/MainDriver.cpp 
- contains the code for driving the program from the command line


** src/scanner/
-This directory contains all of the code for the scanner, and FSAs.

** src/parser/
-This directory will eventually contain the code for the parser

** src/scanner/TestScanner/
- This directory contains all of the code for the Unit Test Executble.
- The unit tests cover the more complex FSA that were implemented. 

//Travis
for factor rule rules 106 and 116 both go to the same place, so we simply chase to always go to rule 106 accepting <FunctionIdentifier> <OptionalActualParameterList> NOT rule 116 for <VariableIdentifier>

(someone else did this for the second half of factorTail, I only did first half)
changed switch statement in factorTail rule so rather than having this:
case MP_FLOAT_DIVIDE:
	logRule(92);
	multiplyingOperator();
	factor();
	factorTail();
	return true;
case MP_TIMES:
	logRule(92);
	multiplyingOperator();
	factor();
	factorTail();
	return true;
we now have something more like:
case MP_FLOAT_DIVIDE:
case MP_TIMES:
	logRule(92);
	multiplyingOperator();
	factor();
	factorTail();
	return true;
Did the same for expression, booleanExpression, block, actualParameter,finalValue
