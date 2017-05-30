/*
 ============================================================================
 Name        : antivirus.c
 Authors     : Bruno Vieira, Julio Renner, Maiara Lange
 Version     :
 Institution : Unisinos
 Description : Antivirus-like application in C
 ============================================================================
 */

//dependências
#include <stdio.h>
#include <stdlib.h>

//variáveis
char* assinatura_virus;
char* files_queue[1];

//funções
void preencher_lista_arquivos(void);
int imprimir_menu_adicao_arquivos(void);
void adicionar_arquivo(char* filename, int index);
void imprimir_lista_arquivos(void);

/**
 * execução principal
 * @maiaralange
 * @brunopv
 */
int main(int argc, char* argv[]) {
	//Verifica se a assinatura do vírus não foi recebida
	if (argc == 1) {
		printf("Assinatura do vírus não recebida.\n");
		exit(1);
	}
	//define a assinatura do vírus de forma global
	assinatura_virus = argv[1];
	//imprime a assinatura de vírus recebida
	printf("Assinatura do vírus: %s\n", assinatura_virus);
	//preenche a lista de arquivos a serem analisados
	preencher_lista_arquivos();
	//imprime a lista de arquivos analisados
	imprimir_lista_arquivos();

	return EXIT_SUCCESS;
}

/**
 * função encarregada de imprimir as instruções e receber a lista de arquivos a serem verificados, preenchendo o vetor de nomes ao final
 * @brunopv
 */
void preencher_lista_arquivos(void) {
	//variáveis
	//opcao entrada
	int opcao;
	//contador de arquivos lidos
	int file_count = 0;

	/**
	 * loop para entrada de n nomes de arquivo para varredura
	 * quando exit_loop == 1, sai do loop
	 */

	while (opcao != 0) {
		opcao = imprimir_menu_adicao_arquivos();
		//validação de opção
		switch (opcao) {
		case 1:
			printf("Digite o nome do arquivo a adicionar: ");
			char filename;
			scanf("%s", &filename);
			adicionar_arquivo(&filename, file_count);
		}
	}
}

/**
 * função que imprime o menu de opções para adição de arquivos à lista de verificação
 */
int imprimir_menu_adicao_arquivos(void) {
	//variáveis
	int opcao;
	//impressão
	printf("Lista de arquivos:\n");
	//lista os arquivos já adicionados
	imprimir_lista_arquivos();
	//imprime menu de opções
	printf("\n1 - Adicionar arquivo à lista");
	printf("0 - Finalizar adição de arquivos");
	//lê da entrada padrão a opção desejada
	scanf("%d", &opcao);
	return opcao;
}

/**
 * função que adiciona um nome de arquivo ao vetor, alocando mais memória para ele se necessário
 * recebe um ponteiro para vetor de caracteres
 * @brunopv
 */
void adicionar_arquivo(char* filename, int index) {
	//testa se filename é nulo
	if (filename == NULL) {
		//exibe mensagem de erro e aborta execução
		perror("Nome do arquivo é nulo!");
	}
	//testa se o indice é maior que o tamanho do vetor
	if (index > (sizeof(files_queue))) {
		//realoca o vetor incrementando em 1 o seu tamanho
		//realloc(&files_queue, (sizeof(files_queue)/sizeof(files_queue[1])) + 1);
	}
	//adiciona ao índice recebido o filename recebido
	files_queue[index] = filename;

}

/**
 * função que imprime a lista de arquivos desejados para varredura
 */
void imprimir_lista_arquivos(void) {
	for (int i = 0; i < sizeof(&files_queue); i++) {
		printf("[%d] = %s\n", i, files_queue[i]);
	}
}
