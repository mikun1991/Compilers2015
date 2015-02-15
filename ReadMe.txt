
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
