
#include "Scanner.h"
#include "Token.h"
#include "Lexeme.h"

#include "stdio.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
    if(argc != 2){
        fprintf(stdout, "Incorrect number of arguments");
        fprintf(stdout, "Correct syntax: mp <filename>");

        return 1;
    }
   
	ifstream inputFile(argv[1]);

	if (!inputFile.is_open()){
		fprintf(stdout, "Could not open file");
		return 1;
	}

	//inputFile.close();

    Scanner inputScanner(argv[1]);

    if(inputFile.is_open()){
    	Token nextToken;
    	do{
			nextToken = inputScanner.getNextToken();
			if (nextToken.getLexeme().getType() == Lexeme::MP_WHITESPACE)
				continue;
			string type = nextToken.getLexeme().typeToName();
			string name = nextToken.getLexeme().getValue();
			int line = nextToken.getLineNumber();
			int column = nextToken.getColumnNumber();
			printf("Found \"%s\",", name.c_str());
			printf("with type %s , line:%d , column:%d \n", type.c_str(), line, column);
    	}
    	while(nextToken.getLexeme().getType() != Lexeme::MP_EOF);
    }

	inputFile.close();

    return 0;

}
