
#include "scanner\Scanner.h"
#include "scanner\Token.h"

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
	}

	inputFile.close();

    Scanner inputScanner(argv[1]);

    if(inputFile.is_open()){
    	Token nextToken;
    	do{
        	nextToken = inputScanner.getNextToken();
			fprintf(stdout, "Found %s ", nextToken.getLexeme().typeToName());
    	}
    	while(nextToken.getLexeme().getType() != Lexeme::LexemeType::MP_EOF);
    }

    return 0;

}
