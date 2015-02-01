
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

    Scanner inputScanner;

    if(inputFile.is_open()){
    	Token nextToken;
    	do{
        	nextToken = inputScanner.getNextToken();

    	}
    	while(nextToken.getLexeme().getType() != Lexeme::EndOfFile);
    }

    return 0;

}
