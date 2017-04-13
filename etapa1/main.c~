#include <stdio.h>
#include <stdlib.h>

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

	while(running)
	{
		token = yylex();
		
		if(!running)
			break;
		
		printf("token: %d (line %d)\n", token, getLineNumber());
	}

	printf("Your program has %d lines\n", getLineNumber()-1);

	return 1;
}
