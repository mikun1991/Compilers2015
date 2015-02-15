#include "Scanner.h"
#include "Token.h"
#include "Lexeme.h"

#include "Resources.h"

#include "stdio.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{

	if (argc != 2){
		fprintf(stdout, "Incorrect number of arguments");
		fprintf(stdout, "Correct syntax: \"mp <filename>\"");
		return 1;
	}


	ifstream inputFile(argv[1]);
	//just do this to make sure that is a valid file
	//the scanner will be responsible for it's own  file pointer

	if (!inputFile.is_open()){
		fprintf(stdout, "Could not open file!!! \nCheck the path and try again");
		return 1;
	}
	
	inputFile.close();

	Scanner inputScanner(argv[1]);
	Token nextToken;

	do{
		nextToken = inputScanner.getNextToken();
		if (nextToken.getLexeme().getType() == LexemeResources::MP_WHITESPACE)
			continue;
		string type = nextToken.getLexeme().typeToName();
		string name = nextToken.getLexeme().getValue();
		int line = nextToken.getLineNumber();
		int column = nextToken.getColumnNumber();
		
		printf("Found \"%s\",", name.c_str());
		printf("with type %s , line:%d , column:%d \n", type.c_str(), line, column);
	
	} while (nextToken.getLexeme().getType() != LexemeResources::MP_EOF);



	return 0;
}
