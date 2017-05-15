#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

int main(int argc, char** argv)
{
	//printf("debug"); 
	if(argc < 2){ // insuficient arguments
        	printf("\nerror : insuficient arguments\n");
		exit(1);}

	if(!open_input(argv[1])) {// couldn't open input file
       		printf("\nerror : couldn't open input file\n");
		exit(1);}

	initMe();

    yyparse();

    //se chegou ate aqui, o programa de input esta correto
    fprintf(stderr,"programa %s aceito\n", argv[1]);
    exit(0);

    return 1;
}
