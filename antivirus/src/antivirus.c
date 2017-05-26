/*
 ============================================================================
 Name        : antivirus.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// Trabalho do Grau B - Antivírus Simplificado
// Alunos: Bruno Peres Vieira, Julio Renner e Maiara Lange

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	//Verifica se a assinatura do vírus foi recebida
	if(argc == 1){
		printf("Assinatura do vírus não recebida.\n");
		exit(1);
	}

	char* assVirus = argv[1];

	printf("Assinatura do vírus: %s\n", assVirus);

	return EXIT_SUCCESS;
}
