#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

int main(int argc, char** argv)
{
	//printf("debug"); 
	if(argc < 2){ // insuficient arguments
        	printf("\nerror : insuficient arguments\n");
		exit(0);}

	if(!open_input(argv[1])) {// couldn't open input file
       		printf("\nerror : couldn't open input file\n");
		exit(1);}

	initMe();

	/*while(isRunning())
	{
		token = yylex();
		
		if(!isRunning())
			break;
		
		printf("token: %d (line %d)\n", token, getLineNumber());
	}
    

	printf("Your program has %d lines\n", getLineNumber()-1);
    */
    yyparse();

    //se chegou ate aqui, o programa de input esta correto
    fprintf(stderr,"programa %s aceito\n", argv[1]);
    // exit(0);	//??

    return 1;
}
