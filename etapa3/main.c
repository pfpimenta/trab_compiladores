#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

extern ASTREE* root;

int writeToFile(char* path, char* programString)
{
	FILE* file;

	file = fopen(path,"w");

	if(file == NULL)
	{
		fprintf(stderr,"ERROR: Couldn't open %s\n",path);
		exit(1);
	}

	fprintf(file,"%s",programString);

	return 1;
}

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

		char* decompiledASTREE = astreeDecompile(root);

	  writeToFile(argv[2],decompiledASTREE);

    //se chegou ate aqui, o programa de input esta correto
    fprintf(stderr,"programa %s aceito\n", argv[1]);
    exit(0);

    return 1;
}
