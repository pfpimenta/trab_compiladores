#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "semantic.h"
#include "asm.h"
#include "tac.h"
#include "y.tab.h"

extern ASTREE* root;
extern int semanticErrorFlag;

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
	TAC* tac;
	//printf("debug");
	if(argc < 2){ // insuficient arguments
        	printf("\nerror : insuficient arguments\n");
		exit(1);}

	if(!open_input(argv[1])) {// couldn't open input file
       		printf("\nerror : couldn't open input file\n");
					exit(1);}


	initMe();

  yyparse();

	//char* decompiledASTREE = astreeDecompile(root);
	//astreePrint(root, 0);
 	//writeToFile(argv[2],decompiledASTREE);

	semanticErrorFlag = 0;
	semanticSetDeclarations(root);
	semanticCheck(root);
	if(semanticErrorFlag)
	{
		//fprintf(stderr, "\ndebug: deu exit(4)\n");
		exit(4);
	}

	tac = tacGenerate(root);
	//tacPrintBack(tac);
	//fprintf(stderr, "\ndebug1\n");

	tacPrintBack(tacReverse(tac));
	//fprintf(stderr, "\ndebug1i1i1\n");
	//tacPrintForward(tacGetFirst(tacReverse(tac)));

	char* asmString = generateAsm(tac);

	writeToFile("teste.s",asmString);

  //se chegou ate aqui, o programa de input esta correto
  fprintf(stderr,"\n\nprograma %s aceito\n", argv[1]);
  exit(0);

  return 1;
}
