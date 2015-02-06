
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
		return 1;
	}

	//inputFile.close();

    Scanner inputScanner(argv[1]);

    if(inputFile.is_open()){
    	Token nextToken;
    	do{
			nextToken = inputScanner.getNextToken();
			if (nextToken.getLexeme().getType() == Lexeme::LexemeType::MP_WHITESPACE)
				continue;
			string type = nextToken.getLexeme().typeToName();
			string name = nextToken.getLexeme().getValue();
			printf("Found \"%s\",", name.c_str());
			printf("with type %s \n", type.c_str());
    	}
    	while(nextToken.getLexeme().getType() != Lexeme::LexemeType::MP_EOF);
    }

	inputFile.close();

    return 0;

}
